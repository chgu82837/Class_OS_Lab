public class Ex1 implements Runnable {
    cnt c;
    boolean toAdd;

    public Ex1(cnt the_cnt,boolean toAdd){
        c = the_cnt;
        this.toAdd = toAdd;
    }

    public synchronized void run() {
        if(toAdd){
            toAdd = !toAdd;
            System.out.printf("Add thread started!%n");
            for (int i =0;i<25000000;i++)
                add();
            System.out.printf("Add thread ended!%n");
            c.print();
        }
        else{
            toAdd = !toAdd;
            System.out.printf("Sub thread started!%n");
            for (int i =0;i<25000000;i++)
                sub();
            System.out.printf("Sub thread ended!%n");
            c.print();
        }
    }

    private void add(){
        c.add();
    }

    private void sub(){
        c.sub();
    }

    public void print() {
        c.print();
    }
    public static void main(String[] args) {
        
        cnt n = new cnt(0);
        Ex1 e = new Ex1(n,true);

        Thread thread0 = new Thread(e) ;
        Thread thread1 = new Thread(e) ;
        Thread thread2 = new Thread(e) ;
        Thread thread3 = new Thread(e) ;

        thread0.start();
        thread1.start();
        thread2.start();
        thread3.start();

        try {
            thread0.join();
            thread1.join();
            thread2.join();
            thread3.join();
        } catch (InterruptedException e0) {}
        n.print();
    }
}
