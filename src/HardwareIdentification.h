#ifndef HOMEWIRE_HARDWARE_HARDWAREIDENTIFICATION_H
#define HOMEWIRE_HARDWARE_HARDWAREIDENTIFICATION_H

// Normal periodic sensor
#if defined(TEMPERATURE) || defined(SOILMOISTURE)
#define SENSOR
#endif

// Reactive event-based sensor
#if defined(MOTION)
#define SENSOR
#define REACTIVE
#endif

// Normal actor
#if defined(RELAY)
#define ACTOR
#endif

#endif //HOMEWIRE_HARDWARE_HARDWAREIDENTIFICATION_H
