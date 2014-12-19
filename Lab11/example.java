public class example implements Runnable {
    public int c = 0;

    public synchronized void run() {
        for (int i =0;i<25000000;i++){
            c++;
        }
    }

    public int getvalue() {
        return c;
    }
    public static void main(String[] args) {
        example Syc = new example();
        // create three threads
        Thread thread0 = new Thread(Syc) ;
        thread0.start();
        Thread thread1 = new Thread(Syc) ;
        thread1.start();
        Thread thread2 = new Thread(Syc) ;
        thread2.start();
        Thread thread3 = new Thread(Syc) ;
        thread3.start();
        // waiting for threads finish
        try {
            thread0.join();
            thread1.join();
            thread2.join();
            thread3.join();
        } catch (InterruptedException e) {}
        System.out.printf("(%d)%n", Syc.getvalue() ) ;
    }
}
