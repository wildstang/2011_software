// A somewhat persistent Hashtable

package edu.neu.nutrons.lib;

import com.sun.squawk.microedition.io.FileConnection;
import java.io.*;
import java.util.Enumeration;
import java.util.Hashtable;
import javax.microedition.io.Connector;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
public class BotConfig extends Hashtable {

    String path;

    public BotConfig(String path) {
        this.path = path;
    }

    public void load() {
        DataInputStream theFile = null;
        FileConnection fc = null;

        try {
            fc = (FileConnection) Connector.open("file:///" + path, Connector.READ);
            theFile = fc.openDataInputStream();
        }
        catch(Exception ex) {
            System.out.println("failed to open data input stream");
        }

        if(fc != null) {
            System.out.println("something might be working?");
            try {
                while(true) {
                    String inputString = theFile.readUTF();
                    int comma = inputString.indexOf(",");
                    String key = inputString.substring(0, comma);
                    double value = 0;
                    value = Double.parseDouble(inputString.substring(comma + 1));
                    System.out.println("Key: " + key + " | val: " + value);
                    this.put(key, value);
                }
            }
            catch(NullPointerException ex) {
                System.out.println("null pointer on file read " + path);
            }
            catch(IOException ex) {
                System.out.println("failed to read file " + path);
            }
            try {
                fc.close();
            }
            catch(IOException ex) {
                System.out.println("failed to close file " + path);
            }
        }
    }

    public void save() {
        DataOutputStream theFile = null;
        FileConnection fc = null;

        try {
            fc = (FileConnection) Connector.open("file:///" + path, Connector.WRITE);
            fc.create();
            theFile = fc.openDataOutputStream();
        }
        catch(Exception ex) {
        }

        if(fc != null) {
            for(Enumeration e = this.keys(); e.hasMoreElements();) {
                Object thisKey = e.nextElement();
                Object obj = this.get(thisKey);
                String nextLine = thisKey.toString() + "," + obj.toString() + "\n";
                try {
                    // theFile.write(nextLine.getBytes(), 0, nextLine.length());
                    theFile.writeUTF(nextLine);
                }
                catch(IOException ex) {
                    System.out.println("failed to load file " + path);
                }
                try {
                    fc.close();
                }
                catch(IOException ex) {
                    System.out.println("failed to close file " + path);
                }
            }
        }
    }

    public void put(String string, double d) {
        this.put(string, new Double(d));
    }
}
