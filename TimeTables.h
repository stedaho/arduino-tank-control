/* Copyright 2017 Stefan Daniel Homfeld, www.stedaho.de */

const long MINUTE = 60;
const long HOUR = 60 * MINUTE;
const float maintenancePercentageValue = 90;

/* Time-value pairs for white channel */
unsigned int valueTableWhite[MAX_VALUES][2] {
  {(7 * HOUR + 50 * MINUTE) / 10, 0},
  {(8 * HOUR + 10 * MINUTE) / 10, 900},
  {(13 * HOUR + 30 * MINUTE) / 10, 900},
  {(13 * HOUR + 45 * MINUTE) / 10, 50},
  {(16 * HOUR + 30 * MINUTE) / 10, 50},
  {(16 * HOUR + 45 * MINUTE) / 10, 900},
  {(21 * HOUR + 50 * MINUTE) / 10, 900},
  {(22 * HOUR + 10 * MINUTE) / 10, 0}
};

/* Time-value pairs for red channel */
unsigned int valueTableRed[MAX_VALUES][2] {
  {(7 * HOUR + 30 * MINUTE) / 10, 0},
  {(7 * HOUR + 50 * MINUTE) / 10, 900},
  {(13 * HOUR + 30 * MINUTE) / 10, 900},
  {(13 * HOUR + 45 * MINUTE) / 10, 50},
  {(16 * HOUR + 30 * MINUTE) / 10, 50},
  {(16 * HOUR + 45 * MINUTE) / 10, 900},
  {(22 * HOUR + 10 * MINUTE) / 10, 900},
  {(22 * HOUR + 30 * MINUTE) / 10, 0}
};

/* Time-value pairs for blue channel */
unsigned int valueTableBlue[MAX_VALUES][2] {
  {(0 * HOUR + 00 * MINUTE) / 10, 0},
  {(8 * HOUR + 10 * MINUTE) / 10, 0},
  {(8 * HOUR + 30 * MINUTE) / 10, 900},
  {(13 * HOUR + 30 * MINUTE) / 10, 900},
  {(13 * HOUR + 45 * MINUTE) / 10, 50},
  {(16 * HOUR + 30 * MINUTE) / 10, 50},
  {(16 * HOUR + 45 * MINUTE) / 10, 900},
  {(21 * HOUR + 30 * MINUTE) / 10, 900},
  {(21 * HOUR + 50 * MINUTE) / 10, 0},
  {(22 * HOUR + 29 * MINUTE) / 10, 0},
  {(22 * HOUR + 30 * MINUTE) / 10, 30}
};
