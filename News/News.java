import java.utils.*;

public class News {

    String author;
    String text;
    String title;
    HashSet<String> tags;
    boolean isRead;
    int nTimesRead;

    public News(String author, String text, String title, HashSet<String> tags) {
        this.author = author;
        this.text = text;
        this.title = title;
        this.tags = tags;
        this.isRead = False;
        this.nTimesRead = 0;
    }

    public void markAsRead() {
        this.isRead = True;
    }

    public void display() {
        System.out.println(this.title);
        System.out.println(this.author);
        System.out.println(this.text);
    }

    public int nOfTags(HashSet<String> targetTags) {
        Set<String> intersection = new HashSet<String>(self.tags);
        intersection.retainAll(targetTags);
        return intersection.size();
    }
}
