/*

    Lick Audio.
    Copyright (c) 2020-2022 held jointly by the individual authors.

    This file is part of Lick Audio.

    Lick Audio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Lick Audio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Lick Audio.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
  pluginInstance = p;

  p->addModel(modelAtan);
  p->addModel(modelFabs);
  p->addModel(modelTanh);
  p->addModel(modelTick);

  // Any other plugin initialization may go here.
  // As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
