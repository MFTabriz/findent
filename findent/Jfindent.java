/* 
 * jfindent: a graphical wrapper for findent, my Fortran indenting program.
 * Take care that jfindent can find the findent executable.
 *
 * This is my first significant java project, I am glad to receive 
 * suggestions for improvements.
 *
 * This program needs java >= 1.7
 *
 * Willem Vermin
 * wvermin@gmail.com
 *
 * Many thanks for all information I found on many places on the WWW
 */
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
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

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
   static final String VERSION = "1.0";
   static final int DOHELP     = 1;
   static final int DOVERSION  = 2;
   boolean optionsToggle = true;
   public static final class OsUtils {
      private static String OS             = null;
      private static String configFileName = null;
      private static String newLine        = null;

      public static String getOsName() {
	 if(OS == null) { 
	    OS = System.getProperty("os.name"); }
	 return OS;
      }
      public static boolean isWindows() {
	 return getOsName().startsWith("Windows");
      }
      public static String getConfigFileName() {
	 if(configFileName == null) {
	    if (isWindows()) {
	       configFileName = System.getProperty("user.home")+".\\jfindent.data";
	    } else {
	       configFileName = System.getProperty("user.home")+"/.jfindentrc";
	    }
	 }
	 return configFileName;
      }
      public static String getNewLine() {
	 if(newLine == null) {
	    newLine = System.getProperty("line.separator");
	 }
	 return newLine;
      }
   }

   class IndentOptions extends JPanel implements ChangeListener {
      static final int minIndent = 0;
      static final int maxIndent = 8;

      JSpinner spinner;
      public IndentOptions() {
	 JLabel indentLabel = new JLabel("Indent:");
	 indentLabel.setToolTipText("specify indentation");

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

      public void stateChanged(ChangeEvent e) {

	 JSpinner source = (JSpinner)e.getSource();
	 indentParm = (int)source.getValue();
	 callFindent(inFile,log,null);
	 writeConfig();
      }
   }

   class FormatOptions extends JPanel implements ActionListener {

      public FormatOptions() {

	 JLabel formatLabel = new JLabel("Input form:");
	 JRadioButton fixedButton = new JRadioButton("fixed");
	 fixedButton.setToolTipText("assume input is in fixed form");
	 JRadioButton freeButton  = new JRadioButton("free");
	 freeButton.setToolTipText("assume input is in free form");
	 JRadioButton autoButton  = new JRadioButton("auto");
	 autoButton.setToolTipText("let findent find out the form");

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

	 switch (fixedfreeParm) {
	    case "fixed": fixedButton.setSelected(true); break;
	    case "free":  freeButton.setSelected(true); break;
	 }

	 add(formatLabel);
	 add(autoButton);
	 add(freeButton);
	 add(fixedButton);
      }

      public void actionPerformed(ActionEvent e) {
	 String s = e.getActionCommand();
	 switch (s) {
	    case "auto":  fixedfreeParm = "auto";  break;
	    case "free":  fixedfreeParm = "free";  break;
	    case "fixed": fixedfreeParm = "fixed"; break;
	 }
	 callFindent(inFile,log,null);
	 writeConfig();
      }
   }

   class ConvertOption extends JPanel implements ActionListener {
      public ConvertOption() {

	 JLabel convertLabel = new JLabel("Fixed->free:");
	 JRadioButton yesButton = new JRadioButton("yes");
	 JRadioButton noButton  = new JRadioButton("no");

	 yesButton.setActionCommand("yes");
	 yesButton.setToolTipText("convert from fixed to free form");
	 noButton.setActionCommand("no");
	 noButton.setToolTipText("do not convert from fixed to free form");

	 yesButton.addActionListener(this);
	 noButton.addActionListener(this);

	 ButtonGroup yesnoGroup = new ButtonGroup();
	 yesnoGroup.add(noButton);
	 yesnoGroup.add(yesButton);

	 noButton.setSelected(true);

	 if (convertParm) {
	    yesButton.setSelected(true);
	 }

	 add(convertLabel);
	 add(noButton);
	 add(yesButton);
      }
      public void actionPerformed(ActionEvent e) {
	 String s = e.getActionCommand();
	 switch (s) {
	    case "yes": convertParm = true;  break;
	    case "no":  convertParm = false; break;
	 }
	 callFindent(inFile,log,null);
	 writeConfig();
      }
   }

   class ExtraOptions extends JPanel implements ActionListener {
      JTextField extraText;
      public ExtraOptions() {

	 JLabel extraLabel = new JLabel("Extra options:");
	 extraText         = new JTextField(extraParm,40);
	 extraText.setToolTipText("type here extra options for findent");
	 extraText.setActionCommand("extra");
	 extraText.addActionListener(this);
	 extraText.setFont(new Font(Font.MONOSPACED,Font.BOLD,14));

	 JButton enterButton   = new JButton("enter");
	 JButton clearButton   = new JButton("clear extra options");
	 JButton optionsButton = new JButton("show all options");
	 enterButton.addActionListener(this);
	 enterButton.setActionCommand("enter");
	 clearButton.addActionListener(this);
	 clearButton.setActionCommand("clear");
	 optionsButton.addActionListener(this);
	 optionsButton.setActionCommand("options");
	 add(extraLabel);
	 add(extraText);
	 add(enterButton);
	 add(clearButton);
	 add(optionsButton);
      }

      public void actionPerformed(ActionEvent e) {
	 switch (e.getActionCommand()){
	    case "clear":   extraParm = "";
			    extraText.setText(extraParm); 
			    break;
	    case "enter": 
	    case "extra":   extraParm = extraText.getText();
			    break;
	    case "options": if (optionsToggle)
			    {
			       callFindent(null,log,null,DOHELP);
			       optionsToggle = false;
			       return;
			    } 
	 }
	 optionsToggle = true;
	 callFindent(inFile,log,null);
	 writeConfig();
      }
   }

   class PreviewOption extends JPanel implements ActionListener {
      public PreviewOption() {

	 JLabel previewLabel    = new JLabel("Preview:");
	 JRadioButton yesButton = new JRadioButton("yes");
	 yesButton.setToolTipText("show preview of indented selected file");
	 JRadioButton noButton  = new JRadioButton("no");
	 noButton.setToolTipText("do not show preview of indented selected file");

	 yesButton.setActionCommand("yes");
	 noButton.setActionCommand("no");

	 yesButton.addActionListener(this);
	 noButton.addActionListener(this);

	 ButtonGroup yesnoGroup = new ButtonGroup();
	 yesnoGroup.add(yesButton);
	 yesnoGroup.add(noButton);

	 yesButton.setSelected(true);

	 if (!previewParm) {
	    noButton.setSelected(true);
	 }

	 add(previewLabel);
	 add(yesButton);
	 add(noButton);
      }

      public void actionPerformed(ActionEvent e) {
	 String s = e.getActionCommand();
	 switch (s) {
	    case "yes": previewParm = true;  break;
	    case "no":  previewParm = false; break;
	 }
	 callFindent(inFile,log,null);
	 writeConfig();
      }
   }

   class Preview implements PropertyChangeListener {
      public Preview() {
      }
      public void propertyChange(PropertyChangeEvent evt) {
	 if (JFileChooser.SELECTED_FILE_CHANGED_PROPERTY == evt.getPropertyName()) {
	    if (evt.getNewValue() != null) {
	       inFile = new File(evt.getNewValue().toString());
	       if (inFile != null) {
		  callFindent(inFile,log,null);
		  fcfolderParm = fc.getCurrentDirectory().getAbsolutePath();
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
	    inputFile.close();
	    return;
	 } catch (Exception e) {
	    errmsg += newline + "Something wrong";
	    try{
	       bw.close();
	       inputFile.close();
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

   public static class FileFormat {
      public enum FileType { WINDOWS, UNIX, MAC, UNKNOWN }

      private static final char CR = '\r';
      private static final char LF = '\n';

      public static FileType discover(String fileName) throws IOException {    

	 Reader reader = new BufferedReader(new FileReader(fileName));
	 FileType result = discover(reader);
	 reader.close();
	 return result;
      }

      private static FileType discover(Reader reader) throws IOException {
	 int c;
	 while ((c = reader.read()) != -1) {
	    switch(c) {        
	       case LF: return FileType.UNIX;
	       case CR: {
			   if (reader.read() == LF) {
			      return FileType.WINDOWS;
			   }
			   return FileType.MAC;
	       }
	       default: continue;
	    }
	 }
	 return FileType.UNKNOWN;
      }
   }

   JFileChooser fc;
   JTextArea log;
   FormatOptions  formatPanel;
   IndentOptions  indentPanel;
   ConvertOption  convertPanel;
   PreviewOption  previewPanel;
   ExtraOptions   extraPanel;

   final static boolean MULTICOLORED = false;
   File inFile = null; // used for preview

   //Specify the look and feel to use.  Valid values:
   //null (use the default), "Metal", "System", "Motif", "GTK+"
   final static String LOOKANDFEEL = "Metal";

   JPanel mainPane;

   static String  extraParm;         // extra parameters for findent
   static String  fixedfreeParm;     // -ifixed -ifree -iauto
   static String  fcfolderParm;      // last used folder
   static String  findentParm;       // path to findent
   static boolean convertParm;       // -ofree
   static boolean previewParm;       // preview on or off
   static int     indentParm;        // -i<n>

   public Jfindent() {
      UIManager.put("FileChooser.readOnly", true);
      readConfig();
      log = new JTextArea(25,130);
      log.setMargin(new Insets(5,5,5,5));
      log.setEditable(false);
      log.setFont(new Font(Font.MONOSPACED,Font.BOLD,12));
      JScrollPane logScrollPane = new JScrollPane(log);
      fc = new JFileChooser(fcfolderParm) {
	 @Override
	 public void approveSelection() {
	    fcfolderParm = getCurrentDirectory().getAbsolutePath();
	    writeConfig();
	    File[] ff = getSelectedFiles();
	       log.setText(null);
	    for ( File f : ff ) {
	       callFindent(f,log,f);
	    }
	 }
	 @Override
	 public void cancelSelection() {
	    System.exit(0);
	 }
      };

      fc.setFont(new Font(Font.MONOSPACED,Font.BOLD,14));
      fc.setAcceptAllFileFilterUsed(true);
      FileNameExtensionFilter filter = new FileNameExtensionFilter(
	    ".f .f90 f95 f03 f08 for ftn", 
	    "f","f90","f95","f03","f08","for","ftn");
      fc.setFileFilter(filter);
      fc.setMultiSelectionEnabled(true);
      fc.setApproveButtonText("indent selected files");
      fc.setApproveButtonToolTipText("indent selected files");
      Preview preview = new Preview();
      fc.addPropertyChangeListener(preview);

      formatPanel  = new FormatOptions();
      indentPanel  = new IndentOptions();
      convertPanel = new ConvertOption();
      extraPanel   = new ExtraOptions();
      previewPanel = new PreviewOption();

      JPanel optionsPanel = new JPanel();
      optionsPanel.add(previewPanel);
      optionsPanel.add(formatPanel);
      optionsPanel.add(convertPanel);
      optionsPanel.add(indentPanel);

      mainPane = new JPanel();
      mainPane.setLayout(new BoxLayout(mainPane, BoxLayout.PAGE_AXIS));
      if (MULTICOLORED) {
	 mainPane.setOpaque(true);
	 mainPane.setBackground(new Color(255, 0, 0));
      }
      mainPane.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
      mainPane.add(fc);
      mainPane.add(optionsPanel);
      mainPane.add(extraPanel);
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

   void readConfig() {
      extraParm     = "";
      convertParm   = false;
      fixedfreeParm = "auto";
      indentParm    = 3;
      previewParm   = true;
      findentParm   = "findent";
      fcfolderParm  = System.getProperty("user.home");

      try {
	 DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	 DocumentBuilder builder = factory.newDocumentBuilder();

	 // Load the input XML document, parse it and return an instance of the
	 // Document class.

	 Document document = builder.parse(new File(OsUtils.getConfigFileName()));
	 NodeList nodeList = document.getDocumentElement().getChildNodes();
	 for (int i = 0; i < nodeList.getLength(); i++) {
	    Node node = nodeList.item(i);

	    if (node.getNodeType() == Node.ELEMENT_NODE) {
	       Element elem = (Element) node;

	       try {
		  extraParm = elem.getElementsByTagName("extra")
		     .item(0).getChildNodes().item(0).getNodeValue();
	       } catch (Exception e) {}

	       try {
		  convertParm = Boolean.parseBoolean(elem.getElementsByTagName("convert")
			.item(0).getChildNodes().item(0).getNodeValue());
	       } catch (Exception e) {}

	       try {
		  previewParm = Boolean.parseBoolean(elem.getElementsByTagName("preview")
			.item(0).getChildNodes().item(0).getNodeValue());
	       } catch (Exception e) {}

	       try {
		  fixedfreeParm = elem.getElementsByTagName("fixedfree").item(0)
		     .getChildNodes().item(0).getNodeValue();
	       } catch (Exception e) {}

	       try {
		  indentParm = Integer.parseInt(elem.getElementsByTagName("indent")
			.item(0).getChildNodes().item(0).getNodeValue());
	       } catch (Exception e) {}

	       try {
		  fcfolderParm = elem.getElementsByTagName("fcfolder").item(0)
		     .getChildNodes().item(0).getNodeValue();
	       } catch (Exception e) {}

	       try {
		  findentParm = elem.getElementsByTagName("findent").item(0)
		     .getChildNodes().item(0).getNodeValue();
	       } catch (Exception e) {}
	    }
	 }
      }
      catch (Exception e) {
      }
   }

   static void writeConfig() {
      try {
	 PrintWriter writer = new PrintWriter(OsUtils.getConfigFileName(),"UTF-8");
	 writer.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	 writer.println("<jfindent>");
	 writer.println("  <parms>");
	 writer.println("    <convert>"   + convertParm    +"</convert>");
	 writer.println("    <fixedfree>" + fixedfreeParm  +"</fixedfree>");
	 writer.println("    <indent>"    + indentParm     +"</indent>");
	 writer.println("    <extra>"     + extraParm      +"</extra>");
	 writer.println("    <fcfolder>"  + fcfolderParm   +"</fcfolder>");
	 writer.println("    <preview>"   + previewParm    +"</preview>");
	 writer.println("    <findent>"   + findentParm    +"</findent>");
	 writer.println("  </parms>");
	 writer.println("</jfindent>");
	 writer.close();
      }
      catch (Exception e) {
      }
   }

   void callFindent(File inFile, JTextArea log, File outFile, Integer... what) {
      // help = true: run findent -h, show output on log
      // outFile = null: output to log, else output to outFile
      // outFile can be the same file as inFile

      // ok, this code got a bit hairy, suggestions are welcome

      boolean doHelp    = false;
      boolean doVersion = false;
      if (what.length == 1){
	 switch (what[0]){
	    case DOHELP:    doHelp = true;
			    break;
	    case DOVERSION: doVersion = true;
			    break;
	 }
      }
      boolean doFile = (outFile != null);
      if (doHelp || doVersion){
	 doFile = false;
      }

      optionsToggle = true;

      String findentExe = findentParm;

      if (findentExe == null){
	 findentExe = "findent";
      }

      if (findentExe.trim().isEmpty()){
	 findentExe = "findent";
      }

      if (!doFile){
	 log.setText(null);
      }

      if (!doHelp){
	 if (!doFile && !previewParm){
	    return;
	 }
      }

      String endl  = OsUtils.getNewLine();
      String fendl = "\n";

      if (!doHelp){
	 if(inFile == null){
	    if (doFile) {
	       log.append("No inputfile ..."+endl);
	       log.setCaretPosition(log.getDocument().getLength());
	    }
	    return;
	 }
	 try{
	    switch(FileFormat.discover(inFile.getAbsolutePath())){
	       case WINDOWS: fendl = "\r\n"; break;
	       case MAC:     fendl = "\r";   break;
	       default:      fendl = "\n";   break;
	    }
	 } catch (Exception e) { 
	    fendl = "\n"; }
      }

      java.util.List<String> parms = new ArrayList<String>();
      parms.add(findentExe);
      if (doHelp){
	 parms.add("-h");
      } else {

	 String s;
	 s = "-i"+fixedfreeParm;
	 parms.add(s);

	 if (convertParm) {
	    s = "-ofree";
	    parms.add(s);
	 }
	 s = "-i"+indentParm;
	 parms.add(s);

	 String[] extraparms = extraParm.split("[ \t]+");
	 for ( String sp : extraparms ){
	    parms.add(sp);
	 }
      }

      ProcessBuilder pb = new ProcessBuilder(parms);
      pb.redirectErrorStream(true);

      Process process = null;
      try {
	 process = pb.start();
      } catch (IOException e) {
	 log.append("Couldn't start findent."+endl);
	 log.append("The command was '"+findentExe+"'"+endl);
	 log.append("Fix this in the 'file->location of findent' menu"+endl);
	 log.setCaretPosition(log.getDocument().getLength());
	 return;
      }

      BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
      BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(process.getOutputStream()));

      int mcount = 1000;
      if (doFile || doHelp){
	 mcount = 0;
      }

      PipeFromFile pipe = null;
      Thread thread = null;
      if (! doHelp){
	 pipe = new PipeFromFile(inFile.getAbsolutePath(),bw,mcount);
	 thread = new Thread(pipe);
	 thread.start();
      }

      int counterin = 0;
      int counterout = 0;

      if (doHelp){
	 log.setText("Findent options:"+endl);
      } else {
	 if (!doFile){
	    log.append("Preview: ");
	 }
      }

      for (String s1: parms){
	 log.append(s1+" ");
      }
      if (!doHelp){
	 log.append(" < "+inFile.getName());
      }
      if (doFile){
	 log.append(" -- ");
      } else {
	 log.append(endl);
      }

      File temp = null;
      Writer writer = null;

      if (doFile){
	 try{
	    temp = File.createTempFile("jfindent", ".tmp");
	 } catch (Exception e) {
	    log.append("Cannot create temp file");
	    log.setCaretPosition(log.getDocument().getLength());
	    return;
	 }

	 try {
	    writer = new BufferedWriter(new OutputStreamWriter(
		     new FileOutputStream(temp), "utf-8"));
	 } catch (Exception e) {
	    log.append("Cannot write to temp file "+temp.getAbsolutePath());
	    log.setCaretPosition(log.getDocument().getLength());
	    try{
	       temp.delete();
	    } catch(Exception ee) {}
	    return;
	 }
      }

      String currLine;
      try {
	 while((currLine = br.readLine()) != null) {
	    counterout++;
	    if (doFile){
	       writer.write(currLine+fendl);
	    } else {
	       if (doHelp){
		  log.append("    ");
	       } else {
		  log.append(String.format("%06d ",counterout));
	       }
	       log.append(currLine+endl);
	    }
	 }
      } catch (IOException e) {
	 log.append(endl+"Couldn't read the output or write to temp file."+endl);
	 log.setCaretPosition(log.getDocument().getLength());
	 if (doFile){
	    try{
	       temp.delete();
	    } catch(Exception ee) {}
	 }
	 return;
      }

      if (doFile) {
	 try{
	    writer.close();
	 } catch (Exception e) {}
      }

      if(!doHelp){
	 String errmsg = pipe.getErrmsg();

	 if (errmsg !=null){
	    log.append(endl+errmsg+endl);
	    log.setCaretPosition(log.getDocument().getLength());
	    if (doFile){
	       try{
		  temp.delete();
	       } catch(Exception e) {}
	    }
	    return;
	 }

	 try{
	    thread.join();
	 } catch (Exception e){}
	 counterin = pipe.getcounterin();
	 if (counterin != counterout){
	    log.append(endl + 
		  "Error: number of input lines("
		  +counterin+") is not equal to number of output lines("
		  +counterout+")"+endl);
	    log.setCaretPosition(log.getDocument().getLength());
	    if (doFile){
	       try{
		  temp.delete();
	       } catch(Exception e) {}
	    }
	    return;
	 }
      }

      if (doFile){
	 try{
	    Files.copy(temp.toPath(),outFile.toPath(),StandardCopyOption.REPLACE_EXISTING);
	 }
	 catch (Exception e){
	    log.append(e.toString());
	    log.append(endl+"Cannot copy from "+temp.getAbsolutePath()+" to "+outFile.getAbsolutePath()+endl);
	    log.setCaretPosition(log.getDocument().getLength());
	    try{
	       temp.delete();
	    } catch(Exception ee) {}
	    return;
	 }
	 log.append("Indented "+counterin+" lines"+endl);
	 log.setCaretPosition(log.getDocument().getLength());
      } else {
	 if (doHelp){
	    log.append("---> end of options <---"+endl);
	 } else {
	    log.append("---> end of preview <---"+endl);
	 }
	 log.setCaretPosition(0);
      }
   }

   static class JfindentMenu implements ActionListener, ItemListener {
      JFrame aboutFrame    = null;
      JFrame versionFrame  = null;
      JFrame helpFrame     = null;

      public JfindentMenu(JFrame frame){
	 JMenuBar menuBar = new JMenuBar();
	 JMenu fileMenu = new JMenu("file");

	 JMenu configMenu = new JMenu("config");

	 JMenuItem fcItem = new JMenuItem("choose location of findent ...");
	 fcItem.setActionCommand("fc");
	 fcItem.addActionListener(this);

	 JMenuItem defaultItem = new JMenuItem("find findent via PATH");
	 defaultItem.setActionCommand("defaultpath");
	 defaultItem.addActionListener(this);

	 configMenu.add(fcItem);
	 configMenu.addSeparator();
	 configMenu.add(defaultItem);

	 JMenuItem quitItem = new JMenuItem("quit");
	 quitItem.setActionCommand("quit");
	 quitItem.addActionListener(this);

	 fileMenu.add(quitItem);

	 JMenu infoMenu = new JMenu("info");

	 JMenuItem versionItem = new JMenuItem ("version");
	 versionItem.setActionCommand("version");
	 versionItem.addActionListener(this);

	 JMenuItem aboutItem = new JMenuItem("Whatis this?");
	 aboutItem.setActionCommand("about");
	 aboutItem.addActionListener(this);

	 infoMenu.add(aboutItem);
	 infoMenu.addSeparator();
	 infoMenu.add(versionItem);

	 JMenuItem helpItem = new JMenuItem("help");
	 helpItem.setActionCommand("help");
	 helpItem.addActionListener(this);


	 menuBar.add(fileMenu);
	 menuBar.add(configMenu);
	 menuBar.add(infoMenu);
	 menuBar.add(helpItem);

	 frame.setJMenuBar(menuBar);
      }
      public void actionPerformed(ActionEvent e){
	 switch(e.getActionCommand()){
	    case "fc":          setFindentLocation();
				break;
	    case "defaultpath": findentParm = "findent";
				writeConfig();
				break;
	    case "quit":        System.exit(0);
	    case "about":       showAbout();
				break;
	    case "version":     showVersion();
				break;
	    case "help":        showHelp();
				break;
	    case "config":      setFindentLocation();
				break;
	    case "doneabout":   aboutFrame.dispose();
				aboutFrame = null;
				break;
	    case "doneversion": versionFrame.dispose();
				versionFrame = null;
				break;
	    case "donehelp":    helpFrame.dispose();
				helpFrame = null;
				break;
	 }
      }

      public void itemStateChanged(ItemEvent e){
      }

      void setFindentLocation(){
	 JFileChooser fileChooser = new JFileChooser();
	 int rc = fileChooser.showOpenDialog(null);
	 if (rc == fileChooser.APPROVE_OPTION){
	    File file = fileChooser.getSelectedFile();
	    System.out.println("FILE:"+file.getAbsolutePath());
	    findentParm = file.getAbsolutePath();
	    writeConfig();
	 }
	 if (rc == fileChooser.CANCEL_OPTION){
	    findentParm = "findent";
	    writeConfig();
	 }
      }

      void showAbout(){
	 if (aboutFrame != null){
	    aboutFrame.setVisible(true);
	    aboutFrame.toFront();
	    return;
	 }
	 aboutFrame = new JFrame("What is this?");
	 JPanel aboutPanel = new JPanel();
	 aboutPanel.setLayout(new BoxLayout(aboutPanel, BoxLayout.PAGE_AXIS));
	 aboutPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
	 JTextArea textArea = new JTextArea();
	 textArea.setFont(new Font(Font.MONOSPACED,Font.BOLD,14));
	 String endl = OsUtils.getNewLine();
	 textArea.append("jfindent is a graphical wrapper for findent"+endl);
	 textArea.append("findent indents Fortran sources"+endl);
	 aboutPanel.add(textArea);
	 JButton doneButton = new JButton("done");
	 doneButton.setActionCommand("doneabout");
	 doneButton.addActionListener(this);
	 aboutPanel.add(doneButton);
	 aboutFrame.add(aboutPanel);
	 aboutFrame.pack();
	 aboutFrame.setVisible(true);
      }

      void showHelp(){
	 if (helpFrame != null){
	    helpFrame.setVisible(true);
	    helpFrame.toFront();
	    return;
	 }
	 helpFrame = new JFrame("help");
	 JPanel helpPanel = new JPanel();
	 helpPanel.setLayout(new BoxLayout(helpPanel, BoxLayout.PAGE_AXIS));
	 helpPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
	 JTextArea textArea = new JTextArea();
	 textArea.setFont(new Font(Font.MONOSPACED,Font.BOLD,14));
	 String endl = OsUtils.getNewLine();
	 textArea.append("Usage:"+endl);
	 textArea.append("Select one or more Fortran sources"+endl);
	 textArea.append("Have a look at the preview, adapt the options to your taste"+endl);
	 textArea.append("and click 'indent'");
	 helpPanel.add(textArea);
	 JButton doneButton = new JButton("done");
	 doneButton.setActionCommand("donehelp");
	 doneButton.addActionListener(this);
	 helpPanel.add(doneButton);
	 helpFrame.add(helpPanel);
	 helpFrame.pack();
	 helpFrame.setVisible(true);
      }

      void showVersion(){
	 if (versionFrame != null){
	    versionFrame.setVisible(true);
	    versionFrame.toFront();
	    return;
	 }
	 versionFrame = new JFrame("version");
	 JPanel versionPanel = new JPanel();
	 versionPanel.setLayout(new BoxLayout(versionPanel, BoxLayout.PAGE_AXIS));
	 versionPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
	 JTextArea textArea = new JTextArea();
	 textArea.setFont(new Font(Font.MONOSPACED,Font.BOLD,14));
	 textArea.append("jfindent version "+VERSION);
	 versionPanel.add(textArea);
	 JButton doneButton = new JButton("done");
	 doneButton.setActionCommand("doneversion");
	 doneButton.addActionListener(this);
	 versionPanel.add(doneButton);
	 versionFrame.add(versionPanel);
	 versionFrame.pack();
	 versionFrame.setVisible(true);
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

      JfindentMenu jfindentMenu = new JfindentMenu(frame);

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
