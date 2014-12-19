import java.util.concurrent.locks.*;
public class ex2 implements Runnable {
        public int c=0,i=0;
	private Lock lock=new ReentrantLock();
        private Condition full = lock.newCondition();
        private Condition empty = lock.newCondition();

        public void run(){
                if(i%2==0){
                i++;
                for(int j=0;j<100;j++){
			lock.lock();
			try{
			if(c==10||c>10){
			empty.await();
			}else{
			c++;
			System.out.printf("product---amount(%d)%n",c);
			full.signal();}
			}catch(InterruptedException e){ e.printStackTrace();}
			finally{
			lock.unlock();
			}
                }
                }else{
                i++;
                for(int j=0;j<100;j++){
                	lock.lock();
			try{
                        if(c==0||c<0){
                        full.await();
                        }else{
			c--;
                        System.out.printf("consume---amount(%d)%n",c);
                        empty.signal();}
                        }catch(InterruptedException e){ e.printStackTrace();}
                        finally{
                        lock.unlock();
                        }     
                }
                }
        }
        public static void main(String[] args) {
        ex2 lll = new ex2();
        Thread thread0=new Thread(lll);
        Thread thread1=new Thread(lll);
        Thread thread2=new Thread(lll);
        Thread thread3=new Thread(lll);

        thread0.start();
        thread1.start();
        thread2.start();
	thread3.start();
        try{
                thread0.join();
                thread1.join();
                thread2.join();
                thread3.join();
        }catch (InterruptedException e) {}
}}

