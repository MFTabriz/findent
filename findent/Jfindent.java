import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.filechooser.*;
import java.io.File;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.ProcessBuilder.Redirect;

public class Jfindent {
   public static final class OsUtils
   {
      private static String OS = null;
      public static String getOsName()
      {
	 if(OS == null) { OS = System.getProperty("os.name"); }
	 return OS;
      }
      public static boolean isWindows()
      {
	 return getOsName().startsWith("Windows");
      }
   }

   class IndentOptions extends JPanel implements ChangeListener
   {
      static final int minIndent = 0;
      static final int maxIndent = 8;
      static final int initIndent = 3;

      private int indent = initIndent;

      public IndentOptions()
      {
	 JLabel indentLabel = new JLabel("Indent:");

	 JSlider indentation = new JSlider(JSlider.HORIZONTAL,
	       minIndent, maxIndent, initIndent);

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
	    indent = (int)source.getValue();
	 }
      }

      public int getIndent()
      {
	 return indent;
      }
   }

   class IndentOptions1 extends JPanel implements ChangeListener
   {
      static final int minIndent = 0;
      static final int maxIndent = 8;
      static final int initIndent = 3;

      private int indent = initIndent;

      JSpinner spinner;
      public IndentOptions1()
      {
	 JLabel indentLabel = new JLabel("Indent:");

	 SpinnerModel spm = new SpinnerNumberModel(initIndent,
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
	 indent = (int)source.getValue();
	 System.out.println(indent);
	 if (indent > maxIndent)
	 {
	    indent = maxIndent;
	    spinner.setValue(indent);
	 }
      }
      public int getIndent()
      {
	 return indent;
      }
   }

   class FormatOptions extends JPanel implements ActionListener 
   {

      private String aff;

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
	 aff = "-iauto";

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
	    case "auto":  aff = "-iauto";  break;
	    case "free":  aff = "-ifree";  break;
	    case "fixed": aff = "-ifixed"; break;
	 }
      }

      public String getFormat()
      {
	 return aff;
      }
   }

   JFileChooser fc;
   JTextArea log;
   FormatOptions formatPanel;
   IndentOptions indentPanel;
   IndentOptions1 indentPanel1;
   final static boolean MULTICOLORED = false;

   //Specify the look and feel to use.  Valid values:
   //null (use the default), "Metal", "System", "Motif", "GTK+"
   final static String LOOKANDFEEL = "Metal";

   JPanel mainPane;

   public Jfindent() {
      UIManager.put("FileChooser.readOnly", true);
      log = new JTextArea(5,80);
      log.setMargin(new Insets(5,5,5,5));
      log.setEditable(false);
      JScrollPane logScrollPane = new JScrollPane(log);
      fc = new JFileChooser()
      {
	 @Override
	 public void approveSelection()
	 {
	    File[] ff = getSelectedFiles();
	    for ( File f : ff )
	    {
	       // System.out.println(f.getName());
	       // System.out.println(f.getAbsolutePath());
	       try 
	       {
		  java.util.List<String> parms = new ArrayList<String>();
		  if (OsUtils.isWindows())
		  {
		     parms.add("cmd");
		     parms.add("/C");
		  }
		  parms.add("wfindent");
		  parms.add(formatPanel.getFormat());
		  parms.add("-i"+indentPanel1.getIndent());
		  parms.add(f.getAbsolutePath());

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
		  log.append(out.toString()+" "+formatPanel.getFormat()+" "
			+" -i"+indentPanel1.getIndent()+" "+f.getName()+"\r\n");
		  log.setCaretPosition(log.getDocument().getLength());

	       }
	       catch (IOException e) 
	       {
		  log.append("Error calling wfindent\r\n");
		  if (OsUtils.isWindows())
		  {
		     log.append("Check if the folder of wfindent.bat and findent.exe is in %PATH%\r\n");
		  }
		  else
		  {
		     log.append("Check if the folder of wfindent and findent is in $PATH\r\n");
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

      formatPanel = new FormatOptions();
      indentPanel = new IndentOptions();
      indentPanel1 = new IndentOptions1();

      JPanel optionsPanel = new JPanel();
      optionsPanel.add(formatPanel);
      //optionsPanel.add(indentPanel);
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
