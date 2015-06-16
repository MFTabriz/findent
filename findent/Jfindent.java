/*
 * Since this source contains code copied from and inspired from Oracle, I
 * inserted the following:
 *
 * Copyright (c) 1995, 2014, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Oracle or the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.filechooser.*;
import java.io.*;
import java.text.*;
import java.lang.ProcessBuilder.Redirect;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import java.beans.*;

import javax.swing.*;


public class Jfindent {
   public static final class OsUtils
   {
      private static String OS             = null;
      private static String configFileName = null;
      private static String newLine        = null;

      public static String getOsName()
      {
	 if(OS == null) { OS = System.getProperty("os.name"); }
	 return OS;
      }
      public static boolean isWindows()
      {
	 return getOsName().startsWith("Windows");
      }
      public static String getConfigFileName()
      {
	 if(configFileName == null)
	 {
	    if (isWindows())
	       configFileName = System.getProperty("user.home")+".\\jfindent.data";
	    else
	       configFileName =  System.getProperty("user.home")+"/.jfindent";
	 }
	 return configFileName;
      }
      public static String getNewLine()
      {
	 if(newLine == null)
	 {
	    newLine = System.getProperty("line.separator");
	 }
	 return newLine;
      }
   }

   class IndentOptions extends JPanel implements ChangeListener
   {
      static final int minIndent = 0;
      static final int maxIndent = 8;

      public IndentOptions()
      {
	 JLabel indentLabel = new JLabel("Indent:");

	 if (indentParm < minIndent)
	    indentParm = minIndent;
	 if (indentParm >maxIndent)
	    indentParm = maxIndent;

	 JSlider indentation = new JSlider(JSlider.HORIZONTAL,
	       minIndent, maxIndent, indentParm);

	 indentation.addChangeListener(this);

	 indentation.setMajorTickSpacing(1);
	 indentation.setMinorTickSpacing(1);
	 indentation.setPaintTicks(true);
	 indentation.setPaintLabels(true);
	 indentation.setBorder(BorderFactory.createEmptyBorder(0,0,10,0));
	 //Font font = new Font("Serif", Font.ITALIC, 15);
	 //indentation.setFont(font);

	 add(indentLabel);
	 add(indentation);

      }
      public void stateChanged(ChangeEvent e) 
      {
	 JSlider source = (JSlider)e.getSource();
	 if (!source.getValueIsAdjusting()) 
	 {
	    indentParm = source.getValue();
	 }
	 showPreview(inFile,log);
	 writeConfig();
      }
   }

   class IndentOptions1 extends JPanel implements ChangeListener
   {
      static final int minIndent = 0;
      static final int maxIndent = 8;

      JSpinner spinner;
      public IndentOptions1()
      {
	 JLabel indentLabel = new JLabel("Indent:");

	 if (indentParm < minIndent)
	    indentParm = minIndent;
	 if (indentParm >maxIndent)
	    indentParm = maxIndent;

	 SpinnerModel spm = new SpinnerNumberModel(indentParm,
	       minIndent, maxIndent,1);
	 spinner = new JSpinner(spm);
	 spinner.setEditor(new JSpinner.DefaultEditor(spinner));

	 spinner.addChangeListener(this);
	 add(indentLabel);
	 add(spinner);
      }

      public void stateChanged(ChangeEvent e)
      {

	 JSpinner source = (JSpinner)e.getSource();
	 indentParm = (int)source.getValue();
	 showPreview(inFile,log);
	 writeConfig();
	 System.out.println("TD:" + indentParm);
      }
   }

   class FormatOptions extends JPanel implements ActionListener 
   {

      public FormatOptions()
      {

	 JLabel formatLabel = new JLabel("Format:");
	 JRadioButton fixedButton = new JRadioButton("fixed");
	 JRadioButton freeButton  = new JRadioButton("free");
	 JRadioButton autoButton  = new JRadioButton("auto");

	 fixedButton.setActionCommand("fixed");
	 freeButton.setActionCommand("free");
	 autoButton.setActionCommand("auto");

	 fixedButton.addActionListener(this);
	 freeButton.addActionListener(this);
	 autoButton.addActionListener(this);

	 ButtonGroup fixfreeGroup = new ButtonGroup();
	 fixfreeGroup.add(autoButton);
	 fixfreeGroup.add(fixedButton);
	 fixfreeGroup.add(freeButton);

	 autoButton.setSelected(true);

	 switch (fixedfreeParm)
	 {
	    case "fixed": fixedButton.setSelected(true); break;
	    case "free":  freeButton.setSelected(true); break;
	 }

	 add(formatLabel);
	 add(autoButton);
	 add(freeButton);
	 add(fixedButton);
      }

      public void actionPerformed(ActionEvent e)
      {
	 String s = e.getActionCommand();
	 switch (s)
	 {
	    case "auto":  fixedfreeParm = "auto";  break;
	    case "free":  fixedfreeParm = "free";  break;
	    case "fixed": fixedfreeParm = "fixed"; break;
	 }
	 System.out.println("TD:"+s);
	 showPreview(inFile,log);
	 writeConfig();
      }
   }

   class ConvertOption extends JPanel implements ActionListener
   {
      public ConvertOption()
      {

	 JLabel convertLabel = new JLabel("Convert fixed->free:");
	 JRadioButton yesButton = new JRadioButton("yes");
	 JRadioButton noButton  = new JRadioButton("no");

	 yesButton.setActionCommand("yes");
	 noButton.setActionCommand("no");

	 yesButton.addActionListener(this);
	 noButton.addActionListener(this);

	 ButtonGroup yesnoGroup = new ButtonGroup();
	 yesnoGroup.add(noButton);
	 yesnoGroup.add(yesButton);

	 noButton.setSelected(true);

	 System.out.println("TD: convertParm"+convertParm);
	 if (convertParm.equals("yes"))
	 {
	    System.out.println("TD1: convertParm"+convertParm);
	    yesButton.setSelected(true);
	 }

	 add(convertLabel);
	 add(noButton);
	 add(yesButton);
      }

      public void actionPerformed(ActionEvent e)
      {
	 String s = e.getActionCommand();
	 switch (s)
	 {
	    case "yes": convertParm = "yes";  break;
	    case "no":  convertParm = "no";  break;
	 }
	 showPreview(inFile,log);
	 writeConfig();
      }
   }

   class Preview implements PropertyChangeListener
   {
      public Preview()
      {
      }
      public void propertyChange(PropertyChangeEvent evt) 
      {
	 if (JFileChooser.SELECTED_FILE_CHANGED_PROPERTY == evt.getPropertyName())
	 {
	    if (evt.getNewValue() != null)
	    {
	       inFile = new File(evt.getNewValue().toString());
	       if (inFile != null)
	       {
		  showPreview(inFile,log);
		  fcFolder = fc.getCurrentDirectory().getAbsolutePath();
		  writeConfig();
	       }
	    }
	 }
      }
   }


   static class PipeFromFile implements Runnable {

      BufferedReader inputFile;
      int maxCount;
      int counterin;
      BufferedWriter bw;
      boolean canRun = true;
      String errmsg;
      static String newline = System.getProperty("line.separator");

      public PipeFromFile(String fileName, BufferedWriter bw, int maxCount){

	 errmsg = null;
	 this.maxCount = maxCount;
	 this.bw = bw;
	 counterin = 0;
	 try{
	    inputFile = new BufferedReader(
		  new InputStreamReader(new FileInputStream(fileName)));
	 } catch (Exception e) {
	    errmsg += newline + "Not found: " + fileName;
	    canRun = false;
	 }
      }

      public void run(){

	 String currInputLine;
	 if (! canRun){
	    errmsg += newline + "Cannot run";
	    try{
	       bw.close();
	    } catch (Exception e) {
	    }
	    return;
	 }
	 try{
	    while((currInputLine = inputFile.readLine()) != null) {
	       counterin++;
	       if (maxCount > 0 && counterin > maxCount){
		  counterin--;
		  break;
	       }
	       bw.write(currInputLine);
	       bw.newLine();
	    }
	    bw.close();
	 } catch (Exception e) {
	    errmsg += newline + "Something wrong";
	    try{
	       bw.close();
	    } catch (Exception e1){
	    }
	 }
      }

      public int getcounterin(){
	 return counterin;
      }

      public String getErrmsg(){
	 return errmsg;
      }
   }


   JFileChooser fc;
   JTextArea log;
   FormatOptions  formatPanel;
   IndentOptions  indentPanel;
   IndentOptions1 indentPanel1;
   ConvertOption  convertPanel;
   final static boolean MULTICOLORED = false;
   File inFile = null; // used for preview

   //Specify the look and feel to use.  Valid values:
   //null (use the default), "Metal", "System", "Motif", "GTK+"
   final static String LOOKANDFEEL = "Metal";

   JPanel mainPane;

   String extraParm;
   String convertParm;
   String fixedfreeParm;
   int indentParm;
   String fcFolder;

   public Jfindent() 
   {
      UIManager.put("FileChooser.readOnly", true);
      readConfig();
      log = new JTextArea(30,130);
      log.setMargin(new Insets(5,5,5,5));
      log.setEditable(false);
      log.setFont(new Font(Font.MONOSPACED,Font.BOLD,14));
      JScrollPane logScrollPane = new JScrollPane(log);
      fc = new JFileChooser(fcFolder)
      {
	 @Override
	 public void approveSelection()
	 {
	    fcFolder = getCurrentDirectory().getAbsolutePath();
	    writeConfig();
	    File[] ff = getSelectedFiles();
	    System.out.println(ff[0].getAbsolutePath());
	    for ( File f : ff )
	    {
	       // System.out.println(f.getName());
	       // System.out.println(f.getAbsolutePath());
	       try 
	       {
		  java.util.List<String> parms = new ArrayList<String>();
		  java.util.List<String> pparms = new ArrayList<String>();
		  if (OsUtils.isWindows())
		  {
		     parms.add("cmd");
		     parms.add("/C");
		  }
		  parms.add("wfindent");
		  pparms.add("wfindent");
		  String s;

		  s = "-i"+fixedfreeParm;
		  parms.add(s);
		  pparms.add(s);

		  if (convertParm.equals("yes"))
		  {
		     s = "-ofree";
		     parms.add(s);
		     pparms.add(s);
		  }
		  s = "-i"+indentParm;
		  parms.add(s);
		  pparms.add(s);

		  parms.add(f.getAbsolutePath());
		  pparms.add(f.getName());

		  ProcessBuilder pb = new ProcessBuilder(parms);
		  pb.redirectErrorStream(true);
		  Process p = pb.start();
		  InputStream in = p.getInputStream();
		  BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		  StringBuilder out = new StringBuilder();
		  String line;
		  while ((line = reader.readLine()) != null) {
		     out.append(line);
		  }
		  reader.close();
		  log.append(out.toString());
		  for ( String ss : pparms)
		     log.append(" "+ss);
		  log.append(OsUtils.getNewLine());
		  log.setCaretPosition(log.getDocument().getLength());

	       }
	       catch (IOException e) 
	       {
		  log.append("Error calling wfindent"+OsUtils.getNewLine());
		  if (OsUtils.isWindows())
		  {
		     log.append("Check if the folder of wfindent.bat and findent.exe is in %PATH%"+OsUtils.getNewLine());
		  }
		  else
		  {
		     log.append("Check if the folder of wfindent and findent is in $PATH"+OsUtils.getNewLine());
		  }
		  log.setCaretPosition(log.getDocument().getLength());
	       }

	    }
	 }
      };

      fc.setAcceptAllFileFilterUsed(true);
      FileNameExtensionFilter filter = new FileNameExtensionFilter(
	    ".f .f90 f95 f03 f08 for ftn", 
	    "f","f90","f95","f03","f08","for","ftn");
      fc.setFileFilter(filter);
      fc.setMultiSelectionEnabled(true);
      fc.setApproveButtonText("indent");
      Preview preview = new Preview();
      fc.addPropertyChangeListener(preview);

      formatPanel  = new FormatOptions();
      indentPanel  = new IndentOptions();
      indentPanel1 = new IndentOptions1();
      convertPanel = new ConvertOption();


      JPanel optionsPanel = new JPanel();
      optionsPanel.add(formatPanel);
      //optionsPanel.add(indentPanel);
      optionsPanel.add(convertPanel);
      optionsPanel.add(indentPanel1);

      mainPane = new JPanel();
      mainPane.setLayout(new BoxLayout(mainPane, BoxLayout.PAGE_AXIS));
      if (MULTICOLORED) {
	 mainPane.setOpaque(true);
	 mainPane.setBackground(new Color(255, 0, 0));
      }
      mainPane.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
      mainPane.add(fc);
      mainPane.add(optionsPanel);
      mainPane.add(logScrollPane);
      mainPane.add(Box.createGlue());
   }


   private static void initLookAndFeel() {
      String lookAndFeel = null;

      if (LOOKANDFEEL != null) {
	 if (LOOKANDFEEL.equals("Metal")) {
	    lookAndFeel = UIManager.getCrossPlatformLookAndFeelClassName();
	 } else if (LOOKANDFEEL.equals("System")) {
	    lookAndFeel = UIManager.getSystemLookAndFeelClassName();
	 } else if (LOOKANDFEEL.equals("Motif")) {
	    lookAndFeel = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
	 } else if (LOOKANDFEEL.equals("GTK+")) { //new in 1.4.2
	    lookAndFeel = "com.sun.java.swing.plaf.gtk.GTKLookAndFeel";
	 } else {
	    System.err.println("Unexpected value of LOOKANDFEEL specified: "
		  + LOOKANDFEEL);
	    lookAndFeel = UIManager.getCrossPlatformLookAndFeelClassName();
	 }

	 try {
	    UIManager.setLookAndFeel(lookAndFeel);
	 } catch (ClassNotFoundException e) {
	    System.err.println("Couldn't find class for specified look and feel:"
		  + lookAndFeel);
	    System.err.println("Did you include the L&F library in the class path?");
	    System.err.println("Using the default look and feel.");
	 } catch (UnsupportedLookAndFeelException e) {
	    System.err.println("Can't use the specified look and feel ("
		  + lookAndFeel
		  + ") on this platform.");
	    System.err.println("Using the default look and feel.");
	 } catch (Exception e) {
	    System.err.println("Couldn't get specified look and feel ("
		  + lookAndFeel
		  + "), for some reason.");
	    System.err.println("Using the default look and feel.");
	    e.printStackTrace();
	 }
      }
   }

   void readConfig()
   {
      extraParm     = "";
      convertParm   = "no";
      fixedfreeParm = "auto";
      indentParm    = 3;
      fcFolder      = System.getProperty("user.home");

      try
      {
	 DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	 DocumentBuilder builder = factory.newDocumentBuilder();

	 // Load the input XML document, parse it and return an instance of the
	 // Document class.

	 Document document = builder.parse(new File(OsUtils.getConfigFileName()));
	 NodeList nodeList = document.getDocumentElement().getChildNodes();
	 System.out.println("TD: nrnodes: "+nodeList.getLength());
	 for (int i = 0; i < nodeList.getLength(); i++) 
	 {
	    Node node = nodeList.item(i);

	    if (node.getNodeType() == Node.ELEMENT_NODE) 
	    {
	       Element elem = (Element) node;

	       // Get the value of the ID attribute.
	       // String ID = node.getAttributes().getNamedItem("ID").getNodeValue();

	       // Get the value of all sub-elements.

	       if (elem.getElementsByTagName("extra").item(0).getChildNodes().getLength()>0)
	       {
		  extraParm = elem.getElementsByTagName("extra")
		     .item(0).getChildNodes().item(0).getNodeValue();
		  System.out.println("TD:extra["+extraParm+"]"+i);
	       }

	       convertParm = elem.getElementsByTagName("convert")
		  .item(0).getChildNodes().item(0).getNodeValue();
	       System.out.println("TD:"+convertParm+" "+i);

	       fixedfreeParm = elem.getElementsByTagName("fixedfree").item(0)
		  .getChildNodes().item(0).getNodeValue();
	       System.out.println("TD:"+fixedfreeParm+" "+i);

	       indentParm = Integer.parseInt(elem.getElementsByTagName("indent")
		     .item(0).getChildNodes().item(0).getNodeValue());
	       System.out.println("TD:"+indentParm+" "+i);

	       if (elem.getElementsByTagName("fcfolder").item(0).getChildNodes().getLength()>0)
	       {
		  fcFolder = elem.getElementsByTagName("fcfolder").item(0)
		     .getChildNodes().item(0).getNodeValue();
		  System.out.println("TD:"+fcFolder+" "+i);
	       }

	    }
	 }
      }
      catch (Exception e)
      {
	 System.out.println("TD: exception in readconfig");
      }
   }

   void writeConfig()
   {
      try
      {
	 PrintWriter writer = new PrintWriter(OsUtils.getConfigFileName(),"UTF-8");
	 writer.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	 writer.println("<jfindent>");
	 writer.println("  <parms>");
	 writer.println("    <convert>"   + convertParm    +"</convert>");
	 writer.println("    <fixedfree>" + fixedfreeParm  +"</fixedfree>");
	 writer.println("    <indent>"    + indentParm     +"</indent>");
	 writer.println("    <extra>"     + extraParm      +"</extra>");
	 writer.println("    <fcfolder>"  + fcFolder       +"</fcfolder>");
	 writer.println("  </parms>");
	 writer.println("</jfindent>");
	 writer.close();
      }
      catch (Exception e)
      {
	 System.out.println("TD: exception in writeConfig");
      }
   }


   void showPreview(File inFile,JTextArea log) {
      if(inFile == null) return;
      String endl = OsUtils.getNewLine();
      log.setText(null);
      java.util.List<String> parms = new ArrayList<String>();
      parms.add("findent");
      String s;

      s = "-i"+fixedfreeParm;
      parms.add(s);

      if (convertParm.equals("yes"))
      {
	 s = "-ofree";
	 parms.add(s);
      }
      s = "-i"+indentParm;
      parms.add(s);

      ProcessBuilder pb = new ProcessBuilder(parms);
      pb.redirectErrorStream(true);

      Process process = null;
      try {
	 process = pb.start();
      } catch (IOException e) {
	 log.append("Couldn't start the process.");
	 log.setCaretPosition(log.getDocument().getLength());
      }

      BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
      BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(process.getOutputStream()));

      PipeFromFile pipe = new PipeFromFile(inFile.getAbsolutePath(),bw,1000);
      Thread thread = new Thread(pipe);
      thread.start();

      int counterin = 0;
      int counterout = 0;

      String currLine;
      try {
	 while((currLine = br.readLine()) != null) {
	    System.out.println(currLine);
	    counterout++;
	    log.append(String.format("%06d ",counterout));
	    log.append(currLine+endl);
	 }
      } catch (IOException e) {
	 System.out.println("Couldn't read the output.");
	 e.printStackTrace();
      }

      String errmsg = pipe.getErrmsg();

      if (errmsg !=null){
	 System.out.println(errmsg);
	 return;
      }

      counterin = pipe.getcounterin();
      System.out.println("---> end of preview <---");
      log.append("---> end of preview <---"+endl);
      log.setCaretPosition(0);
      if (counterin == counterout){
	 System.out.println("counterout == counterin == "+counterin);
      }
      else{
	 System.out.println("counterout = "+counterout+" counterin = "+counterin);
      }
   }


   /**
    * Create the GUI and show it.  For thread safety,
    * this method should be invoked from the
    * event-dispatching thread.
    */
   private static void createAndShowGUI() {
      //Set the look and feel.
      initLookAndFeel();

      //Create and set up the window.
      JFrame frame = new JFrame("Jfindent: indent Fortran sources");
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      //Create and set up the content pane.
      Jfindent jfindent = new Jfindent();
      jfindent.mainPane.setOpaque(true); //content panes must be opaque
      frame.setContentPane(jfindent.mainPane);

      //Display the window.
      frame.pack();
      frame.setVisible(true);
   }

   public static void main(String[] args) {
      //Schedule a job for the event-dispatching thread:
      //creating and showing this application's GUI.
      javax.swing.SwingUtilities.invokeLater(new Runnable() {
	 public void run() {
	    createAndShowGUI();
	 }
      });
   }

}
