import java. util.concurrent.locks.* ;
public class Ex2 implements Runnable {
    private Lock lock;
    private Condition threadCond;
    private int product;
    private int times;
    private int max;
    private boolean isConsumer = false;
    
    public Ex2(int times,boolean isConsumer,int max){
        this.times = times;
        this.isConsumer = isConsumer;
        this.max = max;
        product = 0;
        lock = new ReentrantLock();
        threadCond = lock.newCondition();
    }

    public void produce(){
        lock.lock();
        try {
            while (this.product == max) {
                try {
                    // warehouse is full and producer wait
                    System.out.printf("Full... %n");
                    threadCond.await();
                } catch ( InterruptedException e) {
                    e.printStackTrace ();
                }
            }
            this.product++;
            System.out.printf("To produce (%d) %n" , this.product);
            
            // signal consumer
            threadCond.signal();
        }
        finally {
            lock.unlock();
        }
        for (int i=0;i<1000; i++) {
            
        }
    }

    // call by consumer
    public void consume() {
        lock.lock();
        try {
            while (this.product == 0) {
                try {
                    // no product
                    System.out.printf("Empty... %n");
                    threadCond.await();
                } catch ( InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.printf( "To consume (%d)%n" , this.product ) ;
            this.product--;
            
            //singal producer
            threadCond.signal();
        }
        finally {
            lock.unlock();
        }
        for (int i=0;i<1000; i++) {
            
        }
    }

    public void run() {
        if(isConsumer){
            isConsumer = !isConsumer;
            System.out.printf("consumer thread started!%n");
            for (int i = 0;i<times;i++)
                consume();
            System.out.printf("consumer thread ended!%n");
        }
        else{
            isConsumer = !isConsumer;
            System.out.printf("producer thread started!%n");
            for (int i = 0;i<times;i++)
                produce();
            System.out.printf("producer thread ended!%n");
        }
    }

    public static void main(String[] args){
        Ex2 e = new Ex2(3,false,10);
        int n_th = 10;

        Thread[] th = new Thread[n_th];

        for (int i = 0;i < n_th;i++)
            th[i] = new Thread(e);

        for (int i = 0;i < n_th;i++)
            th[i].start();

        try {
            for (int i = 0;i < n_th;i++)
                th[i].join();
        } catch (InterruptedException e0) {}
    }
}
