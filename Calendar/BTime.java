public class BTime {
  private int hour;
  private int minute;

  BTime(int hour, int minute) {
    this.hour = hour;
    this.minute = minute;
  }

  public int getHour() {
    return hour;
  }

  public int getMinute() {
    return minute;
  }

  public BTime addHalfHour(int halves) {
    BTime newTime = new BTime(this.hour, this.minute);
    for (int i=0; i<halves; i++) {
      if (newTime.minute == 0) {
        newTime.minute = 30;
      }
      else {
        newTime.hour++;
        newTime.minute = 0;
      }
    }
    return newTime;
  }

  public String toString() {
    if (this.minute == 0) {
      return this.hour + ":00";
    }
    else {
      return this.hour + ":30";
    }
  }

  public int difference(BTime time2) {
    if (time2.getMinute() >= minute) {
      return (time2.getHour()-hour)*60 + (time2.getMinute()-minute);
    }
    else {
      return (time2.getHour()-hour-1)*60 + (minute-time2.getMinute());
    }
  }

  public boolean before(BTime time2) {
    if (time2.getHour() > hour) {
      return true;
    }
    else if (time2.getHour() == hour) {
      if (time2.getMinute() > minute) {
        return true;
      }
    }
    return false;
  }

}
