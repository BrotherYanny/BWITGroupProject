import java.utils.*;


public class NewsEngine{
    
    ArrayList<News> news;

    public NewsEngine() {
        ArrayList<News> news = new ArrayList<News>();
    }
    public void displayTopTenNews() {
        news.sort(Comparator.comparing(News::nTimesRead));
        for(int i = 0; i<10, i++) {
            news[i].display()
        }
    }

    public void sortByTags(HashSet<String> targetTags) {
        ArrayList<ArrayList<Integer>> tagMatchCount = new ArrayList<ArrayList<Integer>>();
        forEach(News n : news) {
            int tmpCount = n.nOfTags(targetTags);
            ArrayList<Integer> singleCountEntry = new ArrayList<Integer>(Arrays.asList(n.id, new Integer(tmpCount)));
            tagMatchCount.add(singleCountEntry);
            // sort by tmpCount
        }

    }

    public void displayStoriesForAuthor(String author) {
        forEach(News n : news) {
            if(n.author == author) {
                n.display();
        }
    }
    
}