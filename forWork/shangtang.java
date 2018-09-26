import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int count = scanner.nextInt();
        HashMap<Integer, HashSet<Integer>> map = new HashMap<>();
        for (int i = 0; i < count; i++) {
            int k = scanner.nextInt();
            int v = scanner.nextInt();
            HashSet<Integer> value = map.getOrDefault(k, new HashSet<Integer>());
            value.add(v);
            map.put(k, value);
        }
        for (Integer key : map.keySet()) {
            HashSet<Integer> index = map.get(key);
            for (Integer cur : index){
                for (Integer keys : map.keySet()){
                    if (keys == key){
                        continue;
                    }
                    HashSet<Integer> keysIndex = map.get(keys);
                    if (keysIndex.contains(cur)){
                        keysIndex.addAll(index);
                    }
                }
            }
        }
        int res = 0;
        for (Integer key : map.keySet()){
            res += map.get(key).size();
        }
        System.out.println(res);
    }
}