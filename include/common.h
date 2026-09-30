/* common.h - shared definitions for the ForgeOS Flight Simulator.
 * NOTE: all telemetry is SYNTHETIC. It is not data from real aircraft. */
#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h>

#define NUM_FLIGHTS        6
#define HTTP_PORT          8080
#define HTTP_BIND_ADDR     "127.0.0.1"
#define LOG_PATH           "logs/flight.log"
#define WEB_INDEX          "web/index.html"

#define ALT_WARN_LOW       9500    /* ft: altitude warning below this  */
#define ALT_WARN_HIGH      10500   /* ft: altitude warning above this  */
#define FUEL_LOW_PCT       20      /* %:  low fuel warning at/below    */
#define FUEL_EMERGENCY_PCT 5       /* %:  emergency at/below           */

/* One telemetry sample produced by a flight (child) process. */
typedef struct {
    int tick;
    int altitude;          /* feet   */
    int airspeed;          /* km/h   */
    int fuel;              /* percent */
    int engine_on;
    int altitude_warning;
    int fuel_warning;
    int emergency;
} Telemetry;

/* Message written into the pipe. sizeof(IpcMessage) is far below PIPE_BUF
 * (4096 on Linux), so each write() is atomic: messages from different
 * children can never be interleaved or torn. */
typedef struct {
    int       flight_index;
    pid_t     pid;
    Telemetry data;
} IpcMessage;

typedef struct {
    const char *id;
    const char *name;
    int         start_alt;    /* ft   */
    int         start_speed;  /* km/h */
    double      burn_rate;    /* fuel % per tick (normal mode) */
} FlightConfig;

static const FlightConfig FLIGHT_TABLE[NUM_FLIGHTS] = {
    { "FS101", "Aero One",     10000, 440, 0.12 },
    { "FS202", "Sky Runner",   10400, 470, 0.18 },
    { "FS303", "Cloud Nine",    9700, 420, 0.25 },
    { "FS404", "Falcon Air",   10200, 500, 0.15 },
    { "FS505", "Blue Horizon",  9900, 400, 0.30 },
    { "FS606", "Jet Nova",     10600, 480, 0.21 },
};

#endif
