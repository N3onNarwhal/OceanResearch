# Real-Time Ocean & Weather System
A real-time ocean and dynamic weather system built in Unreal Engine 5,
featuring Gerstner wave simulation, multi-point buoyancy, dynamic weather,
Niagara effects, and custom runtime debugging tools.

Please check out the demo video attached below.

<img width="1339" height="627" alt="Screenshot 2026-08-29 153314" src="https://github.com/user-attachments/assets/ae8d2346-d88d-4d57-8eb6-59e2ebc61d68" />

[![Demo Video](https://youtu.be/l7ApkRS_SgA)](https://youtu.be/l7ApkRS_SgA)

## Features
- Multi-layer Gerstner wave displacement
- Dynamic crest and shoreline foam
- Multi-point physics-based buoyancy
- Boat wake and water interaction effects
- Dynamic wind and weather system
- Rain and ocean splash effects using Niagara
- Volumetric storm clouds and procedural lightning
- Runtime ocean surface sampling
- Custom ocean debugging and profiling tools

## Gerstner Wave Simulation
The ocean surface is generated using multiple Gerstner waves, allowing the water to form directional waves rather than texture-based displacement.
Each wave is controlled by amplitude, wavelength, direction, speed, and steepness. I used multiple waves, combining them to create a more varied surface.
The resulting displacement is applied to the ocean mesh through World Position Offset, while scrolling normal maps provide smaller-scale surface detail.

### Shared Surface Sampling
One of the main challenges was allowing gameplay systems to interact with the same ocean displayed by the material.
I implemented a Gerstner wave calculation on the CPU in addition to the calculations on the GPU that can evaluate the ocean surface at an arbitrary world position.
This provides systems with information such as
- Surface height
- Wave displacement
- Approximate surface normal

The same sampling system is used by buoyancy and runtime debugging tools.

## Water Material
The water material combines large-scale geometric displacement with smaller surface details to give the ocean definition.
The material includes:
- Gerstner wave vertex displacement
- Multiple scrolling normal layers
- Crest and shoreline foam
- Depth-based water coloration
- Configurable roughnmess and surface properties

## Dynamic Buoyancy
The boat in the video (BP_Boat) uses a multi-point buoyancy system.

Several sample points (scene components) are distributed across the boat. Each point queries the ocean surface and determines how far it's submerged, applying buoyancy forces at the individual locations.
Damping is applied to stabilize the simulation and prevent excessive oscillation.

## Boat and Water Interaction
The boat produces additional visual effects based on its interaction with the ocean.
A Niagara-based wake follows the boat as it moves across the surface. 

## Dynamic Weather System
The ocean is connected to a dynamic weather system that allows the environment to transition between calm, cloudy, fog, rain, storm, and heavy storm conditions.
Weather parameters influence multiple systems, including:
- Wave intensity
- Rain
- Cloud coverage
- Fog
- Lightning

Material Parameter Collections are used to share environmental parameters between the ocean material and other systems.

### Weather Transitions
Weather changes can be interpolated or switched instantly.

## Rain and Ocean Interaction
Rain is implemented using Niagara and responds differently depending on the waves of the ocean.

Ocean impacts use the dynamically sampled water surface rather than a static ocean height.
Rain impacts generate separate splash effects for water and land.

## Debugging Tools
Rather than relying solely on visual inspection, I created several runtime debugging and visualization tools for examining the ocean and weather.

### Wave Height Visualization
The wave-height debug grid samples the Gerstner surface across a grid surrounding the player and displays the calculated water height relative to the ocean's base level.
This provides a direct comparison between the rendered waves and the surface values available to gameplay systems.

### Ocean Inspector
The Ocean Inspector allows an arbitrary point on the water to be selected using the mouse cursor.
The select location is evaluated using the sampling system and exposes values such as
- World position
- Surface height
- Wave displacement
- Surface normal

### Performance Monitoring
I also created an in-game performance panel for monitoring the cost of the scene during development, exposing statistics such as:
- FPS
- Frame time
- Game thread time
- Render thread time
- GPU time
- Scene statistics

This tool was primarily used to monitor how changes to the ocean, Niagara effects, and weather systems affected runtime performance.

## Technical Challenges
### Synchronizing Rendering and Gameplay
One of the central challenges was keeping gameplay interactions synchronized with a surface primarily displaced by the material.
The rendered ocean uses WPO, meaning the final displacement can not be directly queried by normal gameplay logic.
To address this, I created a separate ocean sampling system that reproduces the Gerstner calculations at arbitrary world positions.
This allowed buoyancy, rain interaction, and debugging tools to use the same wave motion represented visually by the material.

### Stable Multi-Point Buoyancy
Using multiple buoyancy samples produces more natural motion, but it can also introduce instability when forces vary a lot between points.
I experimented with force strength, dampling, sample placement, and submersion calculations to produce a boat that responds visibly to waves without becoming unstable.

### Interacting with a Dynamically Displaced Surface
Systems sucha s rain and debugging tools can not treat the ocean as a stationary plane because its visual height changes continuouisly.
Instead, these systems query the ocean simulation at the relevant world position to estimate the current surface height.
This allowed effects and debugging information to more closely follow the animated ocean.

## Technology

- Unreal Engine 5.6
- C++
- Blueprint
- Unreal Material Editor
- Niagara
- UMG
- Enhanced Input
- Material Parameter Collections

## Controls
These controls are available to alter on the BP_Character blueprint and corresponding Input Mapping Contexts.

| Input | Action |
| --- | --- |
| WASD | Movement |
| Mouse | Camera |
| Space | Jump |
| Tab | Toggle Debug Panel |
| 1 | Debug Manager Widget |
| 2 | Performance Debug Widget |
| 3 | Ocean Debug Widget |
| 4 | Weather Debug Widget |
| LShift | Toggle Ocean Inspector Widget |
| Left Mouse Click | Update Ocean Inspector Values |
| 5 | Clear Weather |
| 6 | Cloudy Weather |
| 7 | Foggy Weather |
| 8 | Rainy Weather |
| 9 | Storm Weather |
| 0 | Heavy Storm Weather |

## What I Learned
This project gave me an opportunity to explore the relationship between real-time rendering and gameplay simulation rather than treating them as separate systems.
In particular, implementing Gerstner waves as a visual and queryable surface helped me better understand how mathematical calculations can be shared across systems.

The project also reinforced the value of visualization and debugging tools while developing visual systems. Building tools to inspect wave ehights, surface samples, buoyancy forces, and perfomance made it significantly easier to diagnose problems.

## Thank You!
If you got this far, I greatly appreciate the time you took to read through my breakdown. I hope you enjoyed learning more about my project.
