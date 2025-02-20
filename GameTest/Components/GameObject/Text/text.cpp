#include "stdafx.h"

#include <string>

#include "Text.h"

Text::Text(std::string txt) { text = txt; }

std::string Text::getText() { return text; }

void Text::setText(std::string txt) { text = txt; }