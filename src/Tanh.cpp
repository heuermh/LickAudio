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

struct Tanh : Module {
  enum ParamIds {
    NUM_PARAMS
  };
  enum InputIds {
    IN_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    OUT_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds {
    NUM_LIGHTS
  };

  Tanh() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  void process(const ProcessArgs& args) override {
    float v = inputs[IN_INPUT].getVoltage();
    //v = tanh(v);
    v = clamp(v, -5.0, 5.0);
    v = v * (45.0f + v * v) / (45.0f + 15.0 * v * v);
    v = rescale(v, -1.0, 1.0, -5.0, 5.0);
    outputs[OUT_OUTPUT].setVoltage(v);
  }
};

struct TanhWidget : ModuleWidget {
  TanhWidget(Tanh* module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Tanh.svg")));

    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 97.253)), module, Tanh::IN_INPUT));
    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 112.253)), module, Tanh::OUT_OUTPUT));
  }
};

Model* modelTanh = createModel<Tanh, TanhWidget>("Tanh");
