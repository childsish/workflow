# workflow

[![Build Status](https://travis-ci.org/childsish/workflow.svg?branch=master)](https://travis-ci.org/childsish/workflow)

*workflow* is a library that provides a common workflow implementation for projects that use
workflows. The implemented *workflow* is composed of two or more *steps*. Each step can have zero or
more *inputs* and *outputs*. An *output* can be connected to many *inputs*, but an *input* can be
connected to only one *output*. Constructing workflows is simplified into simply piping workflow
steps into each other.

Executing workflows is not implemented nor intended for this library. If you wish to execute
workflows defined and built using this library consider using [mimo][1].

## Simple piping

In the simplest case, a origin step has a single output and target step has a single input. In this
case, piping the steps together will automatically connect the output to the input.

```cpp
#include <workflow/Workflow.h>

workflow::Workflow workflow;
auto step1 = workflow.add_step("step1", {}, {"output"});
auto step2 = workflow.add_step("step2", {"input"}, {});

step1->pipe(step2);
``` 

## Choosing which input/output to pipe to/from

If there are multiple inputs/outputs to choose from, the member variables `Step::get_input` and
`Step:get_output` can be used to distinguish which input or output to use. 

```cpp
#include <workflow/Workflow.h>

workflow::Workflow workflow;
auto step1 = workflow.add_step("step1", {}, {"output1", "output2"});
auto step2 = workflow.add_step("step2", {"input1", "input2"}, {});

step1->get_output("output2")->pipe(step2->get_input("input2"));
```

## Piping an output to multiple input

Outputs can be piped to multiple input. Re-piping a step will not redirect the output from one input
to the other, but rather, direct the output to both inputs.

```cpp
#include <workflow/Workflow.h>

workflow::Workflow workflow;
auto step1 = workflow.add_step("step1", {}, {"output"});
auto step2 = workflow.add_step("step2", {"input1"}, {});
auto step3 = workflow.add_step("step2", {"input2"}, {});

step1->pipe(step2);
step1->pipe(step3);
```

## Steps as keys

`workflow::Step` can be used as keys in std:map and std::unordered_map. 

[1]: https://github.com/childsish/mimo
