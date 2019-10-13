/***************************************************************************************************
 * CLASS: Main (Main.java)
 *
 * DESCRIPTION
 * Main reads 'students.dat' file and stores the information as Student object in an array-list.
 * By an enhanced for loop, a tuition for each Student is calculated by polymorphic method calls. 
 * The tuition is uniquely calculated depending on the type of student (on-campus or online student).
 * The class writes the student list in 'tuition.dat' with the calculated tuitions in descending order
 * based on the amount of the calculated tuitions.  
 * 
 * COURSE AND PROJECT INFO
 * CSE205 Object Oriented Programming and Data Structure, 2019 Spring
 * Project Number: project 03
 *
 * AUTHOR
 * @author Jaehyuk Choi, jchoi154, jchoi154@asu.edu
 **************************************************************************************************/
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Main {

    /**
     * METHOD MAIN
     * Instantiate a Main object and call run() on the object. Note that essentially now, run()
     * becomes the starting point of execution for the program.
     */
    public static void main(String[] pArgs)
    {
    	// instantiates a Main object.
    	Main mainObject = new Main();
    	// calls the run() method. 
    	mainObject.run();
    }

    /**
     * METHOD RUN
     *  Calls other methods to implement the sw requirements.
     *
     * PSEUDOCODE
     * Declare ArrayList<Student> object named studentList and initialize it to null
     *
     * -- In the try-catch block we try to read the list of students from students.dat
     * -- storing the students in the studentList list. If we cannot open the input file for
     * -- reading, then we output an error message and terminate the program.
     * try
     *     studentList = readFile()
     * catch (FileNotFoundException)
     *     Print "Sorry, could not open 'students.dat' for reading. Stopping."
     *     Call System.exit(-100)
     * end try-catch
     *
     * -- Calculate the tuition for each Student in studentList
     * calcTuition(studentList)
     *
     * -- Sort the students in studentList into descending order based on tuition. Read the JavaDoc
     * -- documentation for the MergeSort<E> class for how to use it.
     * Declare and create a MergeSort<Student> object named sorter
     * Call sorter.sort(studentList, Sorter.DESCENDING) to sort the list
     *
     * -- In the try-catch block we try to write the list of students and their calculated tuitions
     * -- to tuition.dat If we cannot open the output file for writing, then we output an error
     * -- message and terminate the program.
     * try
     *     writeFile(studentList)
     * catch (FileNotFoundException)
     *     Print "Sorry, could not open 'tuition.dat' for writing. Stopping."
     *     Call System.exit(-200)
     * end try-catch
     */
    private void run()
    {
    	// The variable list is set and initialized with zeros in the same scope within method run().
    	ArrayList<Student> studentList = null; 
    	
    	// FileNotFoundException for reading
    	try
    	{
    		studentList = readFile("students.dat"); // calls the function readFile().
    	}
    	catch (FileNotFoundException pExcept)
    	{
    		System.out.println("Sorry, could not open 'students.dat' for reading. Stopping.");
    		System.exit(-100);
    	}
    	
    	// calculates the tuition for each Student in studentList
    	calcTuition(studentList);
    	
    	//declares and creates a MergeSort<E> class in Integer.
    	MergeSort<Student> sorter = new MergeSort<>();
    	
        // Call the sort() method on sorter to sort the list.
        sorter.sort(studentList, sorter.DESCENDING);
        
        // FileNotFoundException for writing
        try
        {
        	writeFile(studentList); // calls the function writeFile();
        }
        catch (FileNotFoundException pExcept)
        {
        	System.out.println("Sorry, could not open 'tuition.dat' for writing. Stopping.");
        	System.exit(-200);
        }
    }
    
    /**
     * METHOD CALCTUITION
     * Calculates the tuition for each Student in pStudentList. Write an enhanced for loop that
     * iterates over each Student in pStudentList. For each Student, call calcTuition() on that
     * Student object. Note: this is a polymorphic method call. What does that mean? If you do not
     * know, you need to make sure you understand it. See Ch. 9 in the textbook.
     *
     * PSEUDOCODE
     * ForEach student in pStudentList Do
     *     student.calcTuition()
     * End ForEach
     * 
     * @param pStudentList The {@code ArrayList<E>} pStudentList calculates a tuition.
     */
    private void calcTuition(ArrayList<Student> pStudentList)
    {
    	// Each class Student set up tuition by calling calTuition()
    	for (Student individualStudent: pStudentList)
    	{
    		individualStudent.calcTuition();
    	}
    }

    /**
     * METHOD READFILE
     * Reads the student information from "students.dat" and returns the list of students as
     * an ArrayList<Student> object. Note that this method throws FileNotFoundException if the
     * input file could not be opened. The exception is caught and handled in run().
     *
     * PSEUDOCODE
     * Declare and create an ArrayList<Student> object named studentList
     * Open "students.dat" for reading using a Scanner object named in
     * While in.hasNext() returns true Do
     *     String studentType ← read next string from in
     *     If studentType is "C" Then
     *         studentList.add(readOnCampusStudent(in))
     *     Else
     *         studentList.add(readOnlineStudent(in))
     *     End If
     * End While
     * Close the scanner
     * Return studentList
     * 
     * @param String pFilename 
     * 
     * @return {@code ArrayList<E>} studentList 
     */
    private ArrayList<Student> readFile(String pFilename) throws FileNotFoundException
    {
    	File file = new File(pFilename); // opens File for reading. 
    	
    	Scanner in = new Scanner(file);
    	
    	// studentList is declared and created as a variable. 
    	ArrayList<Student> studentList = new ArrayList<>(); 
    	
    	// reads the Students and add them to the list
    	while (in.hasNext())
    	{
    		// checks if Student in the studentList is OnCampusStudent or OnlineStudent.
    		String studentType = in.next();
    		if (studentType.equals("C"))
    			studentList.add(readOnCampusStudent(in));
    		else
    			studentList.add(readOnlineStudent(in));
    	}
    	
    	in.close(); // closes Scanner object.
    	
    	return studentList;
    }

    /**
     * METHOD READONCAMPUSSTUDENT
     * Reads the information for an on-campus student from the input file.
     *
     * PSEUDOCODE
     * Declare String object id and assign pIn.next() to id
     * Declare String object named lname and assign pIn.next() to lname
     * Declare String object named fname and assign pIn.next() to fname
     * Declare and create an OnCampusStudent object. Pass id, fname, and lname as params to ctor.
     * Declare String object named res and assign pIn.next() to res
     * Declare double variable named fee and assign pIn.nextDouble() to fee
     * Declare int variable named credits and assign pIn.nextInt() to credits
     * If res.equals("R") Then
     *    Call setResidency(OnCampusStudent.RESIDENT) on student
     * Else
     *    Call setResidency(OnCampusStudent.NON_RESIDENT) on student
     * End If
     * Call setProgramFee(fee) on student
     * Call setCredits(credits) on student
     * Return student
     * 
     * @param Scanner pIn  
     * 
     * @return OnCampusStudentObj 
     */
    private OnCampusStudent readOnCampusStudent(Scanner pIn)
    {
    	// reads the information of OnCampusStudent.
    	String id = pIn.next();
    	String lname = pIn.next();
    	String fname = pIn.next();
    	
    	// creates OnCampusStudent object by calling its constructor.
    	OnCampusStudent OnCampusStudentObj = new OnCampusStudent(id, fname, lname);
    	
    	// reads the rest of the info. 
    	String res = pIn.next();
    	double fee = pIn.nextDouble();
    	int credits = pIn.nextInt();
    	
    	// sets up if Student is a resident or a non-resident.
    	if (res.equals("R"))
    		OnCampusStudentObj.setResidency(OnCampusStudentObj.RESIDENT);
    	else
    		OnCampusStudentObj.setResidency(OnCampusStudentObj.NON_RESIDENT);
    	
    	// sets up the program fee and credits to calculate the tuition. 
    	OnCampusStudentObj.setProgramFee(fee);
    	OnCampusStudentObj.setCredits(credits);
    	
    	return OnCampusStudentObj;
    }
    
    /**
     * METHOD READONLINESTUDENT
     * Reads the information for an online student from the input file.
     *
     * PSEUDOCODE
     * Declare String object id and assign pIn.next() to id
     * Declare String object named lname and assign pIn.next() to lname
     * Declare String object named fname and assign pIn.next() to fname
     * Declare and create an OnlineStudent student. Pass id, fname, lname as params to the ctor.,
     * Declare String object named fee and assign pIn.next() to fee
     * Declare int variable named credits and assign pIn.nextInt() to credits
     * If fee.equals("T")) Then
     *     Call setTechFee(true) on student
     * Else
     *     Call setTechFee(false) on student
     * End If
     * Call setCredits(credits) on student
     * Return student
     * 
     * @param Scanner pIn 
     * 
     * @return {@code ArrayList<E>} studentList 
     */
    private OnlineStudent readOnlineStudent(Scanner pIn)
    {
    	// reads the information of OnCampusStudent.
    	String id = pIn.next();
    	String lname = pIn.next();
    	String fname = pIn.next();
    	
    	// creates OnCampusStudent object by calling its constructor.
    	OnlineStudent OnlineStudentObj = new OnlineStudent(id, fname, lname);
    	
    	// reads the rest of the info.
    	String fee = pIn.next();
    	int credits = pIn.nextInt();
    	
    	// sets up if Student needs to pay a technology fee.
    	if (fee.equals("T"))
    		OnlineStudentObj.setTechFee(true);
    	else
    		OnlineStudentObj.setTechFee(false);
    	
    	// sets up the credits to calculate the tuition. 
    	OnlineStudentObj.setCredits(credits);
    	
    	return OnlineStudentObj;
    }
    
    /**
     * METHOD WRITEFILE
     * Writes the output to "tuition.dat" per the software requirements. Note that this method 
     * throws FileNotFoundException if the output file could not be opened. The exception is caught
     * and handled in run().
     *
     * Note, the output can be accomplished using the PrintStream.printf() method, which Print-
     * Writer inherhits since PrintWriter is a subclass of PrintStream.
     *
     * See §2.3.2 in your textbook for a short tutorial on how to use printf().
     *
     * PSEUDOCODE
     * Declare and create a PrintWriter object named out, opening "tuition.dat" for writing
     * ForEach student in pStudentList Do
     *     Using out.printf(), output the student information per SW Requirement 3
     * End ForEach
     * Close the output file
     * 
     * @param pStudentList {@code ArrayList<E>} pStudentList 
     */
    private void writeFile(ArrayList<Student> pStudentList) throws FileNotFoundException
    {
    	// opens 'tuition.dat' for writing
    	PrintWriter out = new PrintWriter("tuition.dat");
    	File output = new File("tuition.dat");
    	
    	// checks if the output exists 
    	System.out.println(output.exists());
    	
    	// prints the student information in the output file.
    	for (Student individualStudent: pStudentList)
    	{
    		out.printf ("%-16s %-20s %-15s %8.2f\n", individualStudent.getID(), individualStudent.getLastName(), individualStudent.getFirstName(), individualStudent.getTuition());
    	}
    	
    	out.close(); // closes the PrintWriter object.
    }
}