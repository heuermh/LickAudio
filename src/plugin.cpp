/*

    heuermh/VCVRack-Plugins.
    Copyright (c) 2020 held jointly by the individual authors.

    This file is part of heuermh/VCVRack-Plugins.

    heuermh/VCVRack-Plugins is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    heuermh/VCVRack-Plugins is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with heuermh/VCVRack-Plugins.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
  pluginInstance = p;

  // Add modules here
  // p->addModel(modelMyModule);
  p->addModel(modelTick);

  // Any other plugin initialization may go here.
  // As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
