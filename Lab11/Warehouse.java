import java. util.concurrent.locks.* ;
public class Warehouse {
    private Lock lock = new ReentrantLock();
    private Condition threadCond = lock.newCondition();
    // -1 warehouse is empty
    private int product = - 1;
    // call by producer
    public void setProduct(int product){
        lock.lock();
        try {
            while (this.product != -1) {
                try {
                    // warehouse is full and producer wait
                    threadCond.await();
                } catch ( InterruptedException e) {
                    e.printStackTrace ();
                }
            }
            this.product = product;
            System.out.printf("To produce (%d) %n" , this.product) ;
            
            // signal consumer
            threadCond.signal();
        }
        finally {
            lock.unlock();
        }
    }

    // call by consumer
    public void getProduct() {
        lock.lock();
        try {
            while (this.product == - 1) {
                try {
                    // no product
                    threadCond.await();
                } catch ( InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.printf( "To consume (%d)%n" , this.product ) ;
            this.product = - 1;
            
            //singal producer
            threadCond.signal();
        }
        finally {
            lock.unlock();
        }
    }
}
