# lubetube
___________________________________________
Hello World! Welcome to the README for the lubetube project (formerly the Liquid Lightsho Arduino)
lubetube is an homage to the classic americana 1960s artform 'liquid lightshow'
Please see our youtube page for some setup pictures, as well as recorded art from the setup:
https://www.youtube.com/@lubetubeliquidlightshow/playlists

___________________________________________
More on the hardware project:
https://github.com/aiaaaa/lubetube
The project is accompanied by an open-source hardware component, which can be explored further at GitHub (more info, schematics, and 3D printable parts to come). This hardware project focuses on a lens liquid handling controller featuring six relays and three gantries. It essentially operates as a pulley system, regulating the distance between two sliding surfaces. The underlying mathematics share some similarities with a swash plate mechanism. Ongoing developments include engineering drawings and the implementation of a new stepper motor setup, intended to replace linear actuators. The motivation behind this shift is rooted in the pursuit of smoother and more fluid movements, prioritizing this quality over the torque stability offered by screw-based actuators.


___________________________________________
A little about Liquid Lighshow,
This style of visual art incorperates:
-a flat lightsourse (historically a overhead projector)
-two concave glass plates (tipically grandfather clock glass)
-two non-miscible solvents with dye (genearlly organic and aqueous)
-a method of projecting or recording the liquid patters generated between the glass layers


Aqueous and Aliphatic Art - Sleepy Sploosh - Soggy Water and Oozy Oleaginous 

This project revolves around the fusion of aqueous and immiscible aliphatic elements, resulting in a unique form of organic liquid art. Drawing inspiration from the mid-century Californian liquid lightshow art form, this avant-garde gorilla art project brings a digital framing of the world of analog visual generation.

Often this was performed at concerts as a way for show-goers to participate in the art. Music shows would often be adorned with multiple classroom style overhead projectors, with water and art supplies. Like a craft project, the concert sidelines would allow everyone a turn to model their own environment and the experience of others. Involving the perceiver in the act of performance.

I use acrylic and oil paint with water. They don’t mix - which is the point. This intentional separation results in an aqueous and oleaginous layering effect.  Mineral oil is utilized to maintain the oil paint layer. This has the added benefit of never drying, preserving its fluidity over time. It ruins the paint as a paint but succeeds in this use case. While this approach may challenge traditional painting techniques, it serves a specific purpose within this artistic context.

In this project we will develop increasinly complex methods of generating these pattersn with robotic actuation.

"Aqueous" - refers to a solution in which water serves as the solvent.
"Aliphatic" - compounds are characterized by straight or branched chains of carbon atoms, encompassing compounds such as alkanes, alkenes, alkynes, and, in this context, mineral oil (composed of branched and circular hydrocarbons).
“Oleaginous” - refers to substances or materials that are oily or greasy in nature. In art, it can refer to the use of oil-based materials or the incorporation of elements with a viscous, oily texture, contributing to the overall aesthetic and texture of the artwork.

https://user-images.githubusercontent.com/38403966/204412633-4971cac1-b3f1-4820-83c8-05f562e10f58.mov

___________________________________________
Builds
Rev1
See video - XXXXXX
This revision utilizes 3 server motors to pull the top glass up and down
I will describe here the layout, pin setup, and general overview

![OverViewRev1](https://user-images.githubusercontent.com/38403966/204412970-02223ea1-54f3-4933-b9f7-65615b919093.jpg)

Rev2
This future revision with utilize stepper motors to give smoother control
