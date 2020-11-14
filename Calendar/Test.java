import java.util.*;
import javafx.util.*;
import java.time.*;

public class Test {

  public static void main(String[] args) {

    Calendar cal = new Calendar();

    List<Integer> meetingParticipants = new ArrayList<>();
    meetingParticipants.add(1);
    meetingParticipants.add(2);

    cal.addMeeting(meetingParticipants, LocalDate.now(), new BTime(14, 00), new BTime(14, 30), "vibe");
    cal.addMeeting(meetingParticipants, LocalDate.now(), new BTime(14, 00), new BTime(14, 30), "vibe2");
    cal.addMeeting(meetingParticipants, LocalDate.now(), new BTime(14, 30), new BTime(15, 30), "vibe3");
    cal.addMeeting(meetingParticipants, LocalDate.now(), new BTime(13, 00), new BTime(16, 00), "vibe4");

    System.out.println("-----------------------------------------------------------------------");

    cal.displayUsersDay(1);

    System.out.println("-----------------------------------------------------------------------");

    cal.displayUsersCalendarForGivenDay(1, LocalDate.now());

    System.out.println("-----------------------------------------------------------------------");

    cal.meetingTimeSuggestion(1, LocalDate.now(), new BTime(13, 00), new BTime(17, 00), 60);

  }
}
