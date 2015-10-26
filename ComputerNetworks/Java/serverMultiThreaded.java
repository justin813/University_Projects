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

    public void run() {
        //Variables
        PrintWriter out;
        BufferedReader in;
        String inputLine;
        String menu = "1. Host current Date and Time\n2. Host uptime\n3. Host memory use\n4. Host Netstat\n5. Host current users\n6. Host running processes\n7. Quit";
        //attempt to set up input and output streams
        try{
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(
                    new InputStreamReader(
                    socket.getInputStream()));
            //return message to client
            out.println("Connection Accepted");
            //loop
            while(true){
                //print out menu
                out.println(menu);
                //let client know server is done messaging
                out.println("Select Menu Option");
                //wait for response
                inputLine = in.readLine();
                //respond with correct response
                out.println(respondData(inputLine));
                //checkes if cmd was the exit Option
                if(Integer.parseInt(inputLine) == 7){
                    break;
                }
                //end of response fix
                out.println("---Response-Compelete---");
            }
            socket.close();
        }
        catch (IOException e) {
            e.printStackTrace();
            return;
        }
        return;
    }
    public static String respondData(String input){
        int value = Integer.parseInt(input);
        String response = null;
        switch(value){
            case 1:
                response = getCommandResults("date");
                break;
            case 2:
                response = getCommandResults("uptime");
                break;
            case 3:
                response = getCommandResults("free -m");
                break;
            case 4:
                response = getCommandResults("netstat");
                break;
            case 5:
                response = getCommandResults("w");
                break;
            case 6:
                response = getCommandResults("ps aux | less");
                break;
            case 7:
                response = "Exit";
                break;
            default:
                response = "Not a vaild selection, please choose";
                break;
        }
        return response;
    }
    public static String getCommandResults(String cmd){
        String data = "";
        String error = "";
        try {
            Process process = Runtime.getRuntime().exec(cmd);
            InputStream in = process.getInputStream();
            File tmp = File.createTempFile("allConnections","txt");
            //attempt to initializing buffers
            BufferedReader stdInput = new BufferedReader(
                new InputStreamReader(process.getInputStream()));
            BufferedReader stdError = new BufferedReader(
                new InputStreamReader(process.getErrorStream()));
            // read the output from the command
            String s = null;
            while ((s = stdInput.readLine()) != null) {
                data += s + "\n";
            }
            while ((s = stdError.readLine()) != null) {
                error += s;
            }
        }
        catch(Exception e){
            data = "error";
        }
        return data;
    }
}
