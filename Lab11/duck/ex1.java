//import java.lang.*;
public class ex1 implements Runnable {
	public int c=0,i=1;	
        public synchronized void run(){
		if(i%2==0){
		i++;
		for(int i=0;i<25000000;i++){
		c++;
		}
		}else{
		i++;
		for(int i=0;i<25000000;i++){
                c--;
		}
		}
	}
	public int getvalue(){
           return c;
	}
	public static void main(String[] args) {
	ex1 Scy = new ex1();
	Thread thread0=new Thread(Scy);
	Thread thread1=new Thread(Scy);
	Thread thread2=new Thread(Scy);
	Thread thread3=new Thread(Scy);
	
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
	System.out.printf("(%d)%n",Scy.getvalue());
}
}
