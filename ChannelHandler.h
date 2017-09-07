/* Copyright 2017 Stefan Daniel Homfeld, www.stedaho.de */

/* Maximum number of switching times per day */
const int MAX_VALUES = 15;

class ChannelHandler {
    unsigned int (&valueTable)[MAX_VALUES][2];
    int numberValues = MAX_VALUES;
    int currentIndex = 0;

  public:
    /* Constructor gets a reference to the time table */
    ChannelHandler(unsigned int (&valueTableParam)[MAX_VALUES][2]) : valueTable(valueTableParam) {
      // TODO Validate times (must be ascending and between 0 and 24h) and values (must be between 0 and 1000)
      /* Determine the number of switching times per day */
      for (int i = 1; i < MAX_VALUES; i++) {
        if (valueTable[i][0] == 0) {
          numberValues = i;
          break;
        }
      }
    }

    /* Calculates the light percentage value at the given time */
    float GetPercentageAtTime(long time) {
      int currentIdx = GetCurrentIndex(time);
      int nextIdx = GetNextIndex();

      float result = CalculateValue(valueTable[currentIdx][0], valueTable[currentIdx][1], valueTable[nextIdx][0], valueTable[nextIdx][1], time);
      return constrain(result, 0, 100);
    }

  private:
    /* Returns the position in the timetable we are at the moment */
    int GetCurrentIndex(long time) {
      FindCurrentIndex(time);
      return currentIndex;
    }

    /* Finds the position in the timetable we are at the moment */
    void FindCurrentIndex(long time) {
      while (!(
               ((long)valueTable[currentIndex][0] * 10 <= time && (long)valueTable[GetNextIndex()][0] * 10 > time) || /* Normally we are between two time value */
               (currentIndex == (numberValues - 1) && (long)valueTable[currentIndex][0] * 10 <= time) || /* End of day, after the last time value */
               (currentIndex == (numberValues - 1) && (long)valueTable[GetNextIndex()][0] * 10 > time) )) { /* Start of day, before the first time value */
        currentIndex = GetNextIndex();
      }
    }

    /* Determines the next index in the timetable */
    int GetNextIndex() {
      if (currentIndex < (numberValues - 1)) {
        return (currentIndex + 1);
      }
      return 0;
    }

    /* Determines the previous index in the timetable */
    int GetPrevIndex() {
      if (currentIndex > 0) {
        return (currentIndex - 1);
      }
      return (numberValues - 1);
    }

    /* Calculates the value at the given time using a linear interpolation between the value at the previous and the next timestamp in the timetable */
    float CalculateValue(long startTime, float startValue, long endTime, float endValue, long time) {
      float timeDiff = ((endTime - startTime) + 8640) % 8640;
      return ((((time - (startTime * 10)) / (timeDiff * 10)) * (endValue - startValue)) + startValue) / 10;
    }
};
