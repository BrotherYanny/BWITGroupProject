import java.util.*;
import javafx.util.*;
import java.time.*;

public class User {

  private int id;
  private String name;
  private String emailAddr;
  private String phoneNo;
  private LocalDate joiningDay;

  User(String name, String emailAddr, String phoneNo) {
    this.id = 0;
    this.name = name;
    this.emailAddr = emailAddr;
    this.phoneNo = phoneNo;
    this.joiningDay = LocalDate.now();
  }

  public int getID() {
    return id;
  }

  public String getName() {
    return name;
  }
  public LocalDate getJoiningDay() {
    return joiningDay;
  }

}
