/*
 *    File:        MONSTRLookAndFeel.cpp
 *
 *    Created:    01/03/2016
 *
 *    This file is part of MONSTR.
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

#include "MONSTRLookAndFeel.h"

#include "UIUtils.h"

MONSTRLookAndFeel::MONSTRLookAndFeel() {
    _regularFont = Font(Typeface::createSystemTypefaceFor(BinaryData::MontserratRegular_ttf,
                                                          BinaryData::MontserratRegular_ttfSize));

    jassert(_regularFont.getTypefaceName().isNotEmpty());
}

MONSTRLookAndFeel::~MONSTRLookAndFeel() {
}

void MONSTRLookAndFeel::drawButtonBackground(Graphics& /*g*/,
                                             Button& /*textButton*/,
                                             const Colour& /*backgroundColour*/,
                                             bool /*shouldDrawButtonAsHighlighted*/,
                                             bool /*shouldDrawButtonAsDown*/) {
    // Do nothing
}

void MONSTRLookAndFeel::drawButtonText(Graphics& g,
                                       TextButton& textButton,
                                       bool /*shouldDrawButtonAsHighlighted*/,
                                       bool /*shouldDrawButtonAsDown*/) {

    if (textButton.isEnabled()) {
        g.setColour(textButton.findColour(TextButton::textColourOnId));
    } else {
        g.setColour(textButton.findColour(TextButton::textColourOffId));
    }

    Font font;
    font.setTypefaceName(getTypefaceForFont(font)->getName());
    g.setFont(font);

    g.drawFittedText(textButton.getButtonText(),
                     0,
                     0,
                     textButton.getWidth(),
                     textButton.getHeight(),
                     Justification::centred,
                     0);
}

void MONSTRLookAndFeel::drawTooltip(Graphics& g,
                                    const String& text,
                                    int width,
                                    int height) {
    g.setColour(UIUtils::lightGrey);
    g.fillRect(0, 0, width, height);

    g.setColour(UIUtils::darkGrey);
    g.drawFittedText(text, 0, 0, width, height, Justification::centred, 3);
}

Typeface::Ptr MONSTRLookAndFeel::getTypefaceForFont(const Font& /*font*/) {
    return _regularFont.getTypeface();
}
