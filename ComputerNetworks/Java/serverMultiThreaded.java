import java.net.*;
import java.io.*;

public class serverMultiThreaded {
    public static void main(String[] args) throws IOException {
        //This is my portNumber
        int portNumber = 3515;

        boolean listening = true;
        try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
            while (listening) {
	            new projectOneMultiServerThread(serverSocket.accept()).start();
	        }
	    } catch (IOException e) {
            System.err.println("Could not listen on port " + portNumber);
            System.exit(-1);
        }
    }
}
class projectOneMultiServerThread extends Thread {
    private Socket socket = null;

    public projectOneMultiServerThread(Socket socket) {
        super("projectOneMultiServerThread");
        this.socket = socket;
    }

    public void run() {``

        try (
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(
                new InputStreamReader(
                    socket.getInputStream()));
        ) {
            String inputLine, outputLine;
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
class projectOne{
    static String netStats;
    public static String getNetStats(){
        final String cmd = "netstat";
        try {

            Process process = Runtime.getRuntime().exec(cmd);

            InputStream in = process.getInputStream();

            File tmp = File.createTempFile("allConnections","txt");

            byte[] buf = new byte[256];

            OutputStream outputConnectionsToFile = new FileOutputStream(tmp);

            int numbytes = 0;

            while ((numbytes = in.read(buf, 0, 256)) != -1) {

                outputConnectionsToFile.write(buf, 0, numbytes);

            }
            netStats = String(outputConnectionsToFile.toByteArray(), CharSet.defaultCharSet());
            System.out.println("File is present at "+tmp.getAbsolutePath());


        } catch (Exception e) {
            e.printStackTrace(System.err);
        }
        return netStats;
    }
}
