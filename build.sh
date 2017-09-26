#!/bin/bash

cmake -H. -B_built && cd _built && make && cp ./main ../


