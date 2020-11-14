import java.util.*;
import javafx.util.*;
import java.time.*;

public class Test {

  // public static Map<Integer, User> userList = new HashMap<>();

  public static void main(String[] args) {

    User rachel = new User("Rachel Yan", "yanrachel.nor@gmail.com", "07776825032");

    System.out.println(rachel.getName());
    // System.out.println(rachel.getEmail());
    // System.out.println(rachel.getPhoneNo());
    System.out.println(rachel.getJoiningDay());

  }
}
