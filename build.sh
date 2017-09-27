#!/bin/bash

cmake -H. -B_built -DCMAKE_BUILD_TYPE=Release && cd _built && make && cp ./turbo-fractal ../


