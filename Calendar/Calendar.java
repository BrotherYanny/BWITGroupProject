import java.util.*;
import javafx.util.*;
import java.time.*;

public class Calendar {

  HashMap<Integer, HashMap<LocalDate, HashMap<Pair<BTime,BTime>, String>>> allCalendars = new HashMap<>(); //Key: UserID, Value: Hashmap

  Calendar() {

  }

  void addMeeting(List<Integer> listOfUsers, LocalDate calendarDay, BTime startTime, BTime endTime, String topic) {
    //is listOfUsers going to be a list of User Objects, or a list of userIDs? Assume ID I think
    for (Integer user : listOfUsers) {
      if (!allCalendars.containsKey(user)) {
        allCalendars.put(user, new HashMap<LocalDate, HashMap<Pair<BTime,BTime>, String>>());
        allCalendars.get(user).put(calendarDay, new HashMap<Pair<BTime,BTime>, String>());
        allCalendars.get(user).get(calendarDay).put(new Pair(startTime, endTime), topic);
        System.out.println(topic + " scheduled for " + startTime.toString() + "-" + endTime + " on " + calendarDay + " for user " + user);
      }
      else {
        for (Pair<BTime, BTime> timePair : allCalendars.get(user).get(calendarDay).keySet()) {
          if ((startTime.getHour() == timePair.getKey().getHour() && startTime.getMinute() == timePair.getKey().getMinute()) //start times are the same
              || (timePair.getKey().before(startTime) && startTime.before(timePair.getValue())) //time1 starts during time2
              || (timePair.getKey().before(endTime) && endTime.before(timePair.getValue())) //time1 ends during time2
              || (startTime.before(timePair.getKey()) && timePair.getValue().before(startTime)) //time2 starts during time1
              || (endTime.before(timePair.getKey()) && timePair.getValue().before(endTime)) //time2 ends during time1
              || (timePair.getKey().before(startTime) && endTime.before(timePair.getValue())) //time1 occurs during time2
              || (startTime.before(timePair.getKey()) && timePair.getValue().before(endTime))) { //time2 occurs during time1
                System.out.println("User " + user + " has a meeting scheduled at this time. " + topic + " could not be scheduled.");
                return;
                // right now this interrupts the function, so if previous people in the list had the meeting successfully added,
                // those meetings would not be cancelled -do we want this?
                // maybe implement it so that all meetings are added at the end after everyone's schedules are checked?
              }
        }
        allCalendars.get(user).get(calendarDay).put(new Pair(startTime, endTime), topic);
        System.out.println(topic + " scheduled for " + startTime.toString() + "-" + endTime.toString() + " on " + calendarDay + " for user " + user);
      }
    }
  }

  void displayUsersDay(int userID) {
    if (!allCalendars.containsKey(userID))
      return;
    System.out.println("User " + userID + "'s calendar for today is as follows: ");
    // LinkedList<Pair<Pair<BTime,BTime>, String>> orderedDayCalendar = new LinkedList<>();
    LocalDate date = LocalDate.now();
    //how to sort by time?
    if (allCalendars.containsKey(userID)) {
      for (Map.Entry<Pair<BTime, BTime>, String> timePair : allCalendars.get(userID).get(date).entrySet()) {
        System.out.println(timePair.getKey().getKey() + "-" + timePair.getKey().getValue() + ": " + timePair.getValue());
      }
    }
  }

  void displayUsersCalendarForGivenDay(int userID, LocalDate calendarDay) {
    if (!allCalendars.containsKey(userID))
      return;
    System.out.println("User " + userID + "'s calendar for " + calendarDay + " is as follows: ");
    // LinkedList<Pair<Pair<BTime,BTime>, String>> orderedDayCalendar = new LinkedList<>();
    for (Map.Entry<Pair<BTime, BTime>, String> timePair : allCalendars.get(userID).get(calendarDay).entrySet()) {
      System.out.println(timePair.getKey().getKey() + "-" + timePair.getKey().getValue() + ": " + timePair.getValue());
    }
  }

  void meetingTimeSuggestion(int organisingUser, LocalDate calendarDay, BTime earliestTime, BTime latestTime,
  int timeInterval) { //assume timeInterval in minutes
    if (!allCalendars.containsKey(organisingUser)) {
      System.out.println("Anytime between " + earliestTime.toString() + " and " + latestTime.toString() + " are ok.");
      return;
    }
    System.out.println("The recommended meeting times are: ");
    for (int i=0; i<=(earliestTime.difference(latestTime)-timeInterval)/30; i++) {
    Pair<BTime, BTime> checkTime = new Pair(earliestTime.addHalfHour(i), earliestTime.addHalfHour(i+(timeInterval/30)));
    Boolean timeOkay = true;
    if (allCalendars.get(organisingUser).containsKey(calendarDay)) {
      for (Pair<BTime, BTime> timePair : allCalendars.get(organisingUser).get(calendarDay).keySet()) {
        if ((earliestTime.addHalfHour(i).getHour() == timePair.getKey().getHour() && earliestTime.addHalfHour(i).getMinute() == timePair.getKey().getMinute()) //start times are the same
            || (earliestTime.addHalfHour(i+(timeInterval/30)).getHour() == timePair.getValue().getHour() && earliestTime.addHalfHour(i+(timeInterval/30)).getMinute() == timePair.getValue().getMinute()) //end times are the same
            || (timePair.getKey().before(earliestTime.addHalfHour(i)) && earliestTime.addHalfHour(i).before(timePair.getValue())) //time1 starts during time2
            || (timePair.getKey().before(earliestTime.addHalfHour(i+(timeInterval/30))) && earliestTime.addHalfHour(i+(timeInterval/30)).before(timePair.getValue())) //time1 ends during time2
            || (earliestTime.addHalfHour(i).before(timePair.getKey()) && timePair.getValue().before(earliestTime.addHalfHour(i))) //time2 starts during time1
            || (earliestTime.addHalfHour(i+(timeInterval/30)).before(timePair.getKey()) && timePair.getValue().before(earliestTime.addHalfHour(i+(timeInterval/30)))) //time2 ends during time1
            || (timePair.getKey().before(earliestTime.addHalfHour(i)) && earliestTime.addHalfHour(i+(timeInterval/30)).before(timePair.getValue())) //time1 occurs during time2
            || (earliestTime.addHalfHour(i).before(timePair.getKey()) && timePair.getValue().before(earliestTime.addHalfHour(i+(timeInterval/30))))) { //time2 occurs during time1
              timeOkay = false;
              break;
            }
      }
    }
    if (timeOkay)
      System.out.println(earliestTime.addHalfHour(i) + "-" + earliestTime.addHalfHour(i+(timeInterval/30)));
    }
  }
}
