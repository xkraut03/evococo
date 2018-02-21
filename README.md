# EvoCoCo

This application automatically builds an image filter (using Evolutionary algorithm), which could be eventually implemented in hardware in portable devices. The aim is to find/develp a configurable filter, which could be configured during filtering to a certain precision/sharpness to save energy (battery) if needed.

### **Evo**lution of a **Co**nfigurable **Co**mponent

#### Build requirements
* C++17 compiler
* GNU Make

#### Idea behind the technology

Not all of computations in our smart devices are done by the main CPU. These devices also contain separate hardware components which were designed to do specific tasks faster and more efficient than CPU. Network chips, image encoder, etc.

But what if you are not a hardware designer? Automatization - using evolutionary algorithms - in this field is not a revolutionary approach, you can find many examples (used in production) online. Using CGP, the component is composed out of blocks implementable in hardware. We have mentioned image filter (and implemented so far in this project) but applicability is wider.

If you take an median image filter, you can (hopefully) make a shortcut during the calculation and produce not so precise image but with less operations, thus saving energy.

Credits to Prof. Ing. Lukáš Sekanina, Ph.D., who is the guarantee and the lecturer of Bio-Inspired Computers course in Brno University of Technology, Faculty of Information Technology. He teaches the EA (and much more) and came up with and idea for this project (he has already done some work in this field).

### Project goals

- [x] Come up with a name
- [x] Working evolution-found filter
- [ ] 1st prototype of working solution (**configurable** filter)
- [ ] Speed up the dumb=slow prototype
- [ ] Create UI for visualisation of both process and result

### License

[Apache License 2.0](LICENSE)
