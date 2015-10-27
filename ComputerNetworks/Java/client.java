//Java version of project one.
/*
    Author: Nagvarun Kanaparthy
*/
import java.io.*;
import java.net.*;

public class client {
    public static void main(String[] args) throws IOException {
        String hostName = "139.62.210.150";
        int port = 3515;
        Socket clientSocket = new Socket(hostName, port);
        //Attempt To open communications between the server and client
        if(clientSocket != null){
        try(
            //Attempt to create the reciving and outputing communications
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream()));
        ){
            //if Successful start reading user's input via a buffer stream
            BufferedReader userInput =
                new BufferedReader(new InputStreamReader(System.in));
            //Create
            String serverResponse;
            String userResponse;
            while ((serverResponse = in.readLine()) != null) {
                System.out.println(serverResponse);
                //the program to exit uses the string "Exit\n"
                if (serverResponse.equals("Exit")){
                    System.out.println("Goodbye Program Exiting\n");
                    break;
                }
                //reads user's input and forwards it to the Server
                if(serverResponse.equals("Select Menu Option")){
                    userResponse = userInput.readLine();
                    if (userResponse != null) {
                        out.println(userResponse);
                    }
                }
            }
        }
        catch (IOException e) {
            System.err.println(e.toString());
        }
    }
    clientSocket.close();
    }
}
