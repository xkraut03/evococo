# EvoCoCo

## Evolution of a Configurable Component
###### Project idea descritpion

Not all of computations in our smart devices are done by the main CPU. These devices also contain separate hardware **components** which were designed to do specific tasks faster and more efficient than CPU. Network chips, image encoder, etc.

I am not a hardware designer. I am a programmer. It would take me at least months to come up with a working component. But I can write a program which does that for me. That's where the **evolution** park comes in. It is not a new concept using evolutionary algorithms in this field and they are actually really good in it. This project uses CGP to genetically design  (artifically) a hardware component.

But what's up with the **configurable** component? Well sometimes we do not need the component to do its job 100% acuratelly. Let's take a *median image filter*. Its purpose is to remove noise in images. How does it do that? For **every** pixel the algorithm takes a few surrounding pixel, does a series of computations and sets a new color according to the result. But we may not need the best result for whole image if we are interested only in a quarter of it or maybe our device is low on battery so we can save up some battery life and be happy with a tiny bit worse looking image (our devices actually do that already sometimes).

Neither I am an expert in the EA area nor this is originaly my idea. Credits to
Prof. Ing. Lukáš Sekanina, Ph.D., who is the guarantee and the lecturer of Bio-Inspired Computers course in Brno University of Technology, Faculty of Information Technology. He teaches the EA (and much more) and came up with and idea for this project (he has already done some work in this field).

### Goals

* Implement a working solution (the school version was semi-finished)
* Iterate and improve the solution
* Learn new techniques, technologies
