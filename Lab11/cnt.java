public class cnt{
    private int content;
    public cnt(int init_value){
        this.content = init_value;
    }

    public void add(){
        this.content++;
    }

    public void sub(){
        this.content--;
    }

    public void print(){
        System.out.printf("Value = %d%n",content);
    }
}
