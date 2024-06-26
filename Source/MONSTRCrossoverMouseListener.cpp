/*
 *	File:		MONSTRCrossoverMouseListener.cpp
 *
 *	Created:	21/01/2021
 *
 *	This file is part of MONSTR.
 *
 *  MONSTR is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MONSTR is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with MONSTR.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MONSTRCrossoverMouseListener.h"

#include <algorithm>

#include "UIUtils.h"
#include "WEFilters/StereoWidthProcessorParameters.h"

MONSTRCrossoverMouseListener::MONSTRCrossoverMouseListener(MonstrAudioProcessor* newAudioProcessor)
        : _processor(newAudioProcessor),
          _widthValueLabel(nullptr),
          _tooltipLabel(nullptr) {

    // Initialise the parameter interactions

    const double defaultWidth {WECore::StereoWidth::Parameters::WIDTH.defaultValue};

    for (int bandIndex {0}; bandIndex < WECore::MONSTR::Parameters::NUM_BANDS.maxValue; bandIndex++) {

        _bandWidths[bandIndex] = FloatParameterInteraction(
            [bandIndex, this](const MouseEvent& event) {
                _processor->setParameterValueInternal(_processor->bandParameters[bandIndex].width, UIUtils::YPosToWidthValue(event.getPosition().getY(), event.eventComponent->getHeight()));
            },
            [bandIndex, defaultWidth, this]() { _processor->setParameterValueInternal(_processor->bandParameters[bandIndex].width, defaultWidth); },
            [bandIndex, this]() { _processor->bandParameters[bandIndex].width->beginChangeGesture(); },
            [bandIndex, this]() { _processor->bandParameters[bandIndex].width->endChangeGesture(); }
        );
    }

    for (int bandIndex {0}; bandIndex < WECore::MONSTR::Parameters::NUM_BANDS.maxValue - 1; bandIndex++) {

        _crossoverFrequencies[bandIndex] = FloatParameterInteraction(
            [bandIndex, this](const MouseEvent& event) {
                constexpr double MIN_SPACING {
                    2 * UIUtils::SLIDER_THUMB_RADIUS + UIUtils::BAND_BUTTON_WIDTH
                };

                const int currentXPos {event.getPosition().getX()};
                const int componentWidth {event.eventComponent->getWidth()};

                _processor->setCrossoverFrequency(bandIndex, UIUtils::XPosToSliderValue(currentXPos, componentWidth));

                // Check if this crossover handle is getting too close to another and move it if
                // needed
                for (int crossoverIndex {0}; crossoverIndex < _processor->numBands->get() - 1; crossoverIndex++) {
                    const double otherXPos {
                        UIUtils::sliderValueToXPos(_processor->crossoverParameters[crossoverIndex]->get(), componentWidth)
                    };

                    const double requiredGap {MIN_SPACING * std::abs(bandIndex - crossoverIndex)};
                    const double actualGap {std::abs(currentXPos - otherXPos)};

                    if (crossoverIndex < bandIndex && actualGap < requiredGap) {
                        _processor->setCrossoverFrequency(crossoverIndex, UIUtils::XPosToSliderValue(currentXPos - requiredGap, componentWidth));
                    } else if (crossoverIndex > bandIndex && actualGap < requiredGap) {
                        _processor->setCrossoverFrequency(crossoverIndex, UIUtils::XPosToSliderValue(currentXPos + requiredGap, componentWidth));
                    }
                }
            },
            []() { /* Do nothing - doesn't have a default to reset to */ },
            [bandIndex, this]() { /* Do nothing - parameter isn't public so no need to send change gesture */ },
            [bandIndex, this]() { /* Do nothing - parameter isn't public so no need to send change gesture */ }
        );
    }

}

MONSTRCrossoverMouseListener::~MONSTRCrossoverMouseListener() {
}

void MONSTRCrossoverMouseListener::mouseMove(const MouseEvent& event) {
    _updateWidthValueLabel(event);
    _updateTooltip(event);
}

void MONSTRCrossoverMouseListener::mouseExit(const MouseEvent& /*event*/) {
    // Clear the width label if the cursor isn't inside the component
    if (_widthValueLabel != nullptr) {
        _widthValueLabel->stop();
    }
}

void MONSTRCrossoverMouseListener::mouseDown(const MouseEvent& event) {
    _dragParameter = _resolveParameterInteraction(event);
    _dragParameter.beginGesture();
}

void MONSTRCrossoverMouseListener::mouseDrag(const MouseEvent& event) {
    _dragParameter.dragCallback(event);
}

void MONSTRCrossoverMouseListener::mouseUp(const MouseEvent& /*event*/) {
    _dragParameter.endGesture();
    _dragParameter = FloatParameterInteraction();
}

void MONSTRCrossoverMouseListener::mouseDoubleClick(const MouseEvent& event) {
    // This implements "double click to default" for the width parameters
    _resolveParameterInteraction(event).resetToDefault();
}

MONSTRCrossoverMouseListener::FloatParameterInteraction MONSTRCrossoverMouseListener::_resolveParameterInteraction(const MouseEvent& event) {
    const int mouseDownX {event.getMouseDownX()};
    const int mouseDownY {event.getMouseDownY()};

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};

    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {bandIndex < numBands - 1 ?
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), event.eventComponent->getWidth()) :
            event.eventComponent->getWidth()
        };

        if (UIUtils::getButtonBounds(crossoverXPos, 0).contains(mouseDownX, mouseDownY)) {
            // Landed on the bypass button
            AudioParameterBool* thisParameter = _processor->bandParameters[bandIndex].isActive;
            _processor->setParameterValueInternal(thisParameter, !thisParameter->get());
            break;

        } else if (UIUtils::getButtonBounds(crossoverXPos, 1).contains(mouseDownX, mouseDownY)) {
            // Landed on the mute button
            AudioParameterBool* thisParameter = _processor->bandParameters[bandIndex].isMuted;
            _processor->setParameterValueInternal(thisParameter, !thisParameter->get());
            break;

        } else if (UIUtils::getButtonBounds(crossoverXPos, 2).contains(mouseDownX, mouseDownY)) {
            // Landed on the solo button
            AudioParameterBool* thisParameter = _processor->bandParameters[bandIndex].isSoloed;
            _processor->setParameterValueInternal(thisParameter, !thisParameter->get());
            break;

        } else if (mouseDownX < crossoverXPos - UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Click landed below a crossover handle but outside a button, so must be on the width
            return _bandWidths[bandIndex];
        } else if (mouseDownX < crossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Click landed on a crossover handle
            return _crossoverFrequencies[bandIndex];
        }
    }

    return FloatParameterInteraction();
}

void MONSTRCrossoverMouseListener::_updateWidthValueLabel(const MouseEvent& event) {
    const int mouseDownX {event.getMouseDownX()};

    // For each available band, check if the cursor is currently inside it
    const int numBands {_processor->numBands->get()};

    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {bandIndex < numBands - 1 ?
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), event.eventComponent->getWidth()) :
            event.eventComponent->getWidth()
        };

        if (mouseDownX < crossoverXPos) {
            // Pass the parameter to the value label
            if (_widthValueLabel != nullptr) {
                _widthValueLabel->setTargetParameter(_processor->bandParameters[bandIndex].width);
            }

            if (_tooltipLabel != nullptr) {
                _tooltipLabel->setText("Band " + juce::String(bandIndex), juce::NotificationType::dontSendNotification);
            }
            break;
        }
    }
}

void MONSTRCrossoverMouseListener::_updateTooltip(const MouseEvent& event) {
    const int mouseDownX {event.getMouseDownX()};
    const int mouseDownY {event.getMouseDownY()};

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};

    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {bandIndex < numBands - 1 ?
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), event.eventComponent->getWidth()) :
            event.eventComponent->getWidth()
        };

        if (UIUtils::getButtonBounds(crossoverXPos, 0).contains(mouseDownX, mouseDownY)) {
            // Landed on the bypass button
            if (_tooltipLabel != nullptr) {
                _tooltipLabel->setText("Bypasses the width processing for this band", juce::NotificationType::dontSendNotification);
            }
            break;

        } else if (UIUtils::getButtonBounds(crossoverXPos, 1).contains(mouseDownX, mouseDownY)) {
            // Landed on the mute button
            if (_tooltipLabel != nullptr) {
                _tooltipLabel->setText("Mutes this band", juce::NotificationType::dontSendNotification);
            }
            break;

        } else if (UIUtils::getButtonBounds(crossoverXPos, 2).contains(mouseDownX, mouseDownY)) {
            // Landed on the solo button
            if (_tooltipLabel != nullptr) {
                _tooltipLabel->setText("Soloes this band", juce::NotificationType::dontSendNotification);
            }
            break;

        } else if (mouseDownX < crossoverXPos - UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Landed below a crossover handle but outside a button, so must be on the width
            if (_tooltipLabel != nullptr) {
                _tooltipLabel->setText("Drag up or down to increase or decrease the stereo width of this band", juce::NotificationType::dontSendNotification);
            }
            break;

        } else if (mouseDownX < crossoverXPos + UIUtils::SLIDER_THUMB_TARGET_WIDTH) {
            // Landed on a crossover handle
            if (_tooltipLabel != nullptr) {
                _tooltipLabel->setText("Drag left or right to change the crossover frequency", juce::NotificationType::dontSendNotification);
            }
            break;
        }
    }
}

