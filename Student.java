/***************************************************************************************************
 * CLASS: Student
 *
 * DESCRIPTION
 * Student is an abstract superclass for the OnCampusStudent and OnlineStudent classes. 
 *
 * COURSE AND PROJECT INFO
 * CSE205 Object Oriented Programming and Data Structure, 2019 Spring
 * Project Number: project 03
 *
 * AUTHOR
 * @author Jaehyuk Choi, jchoi154, jchoi154@asu.edu
 **************************************************************************************************/
public abstract class Student implements Comparable<Student> 
{

    // Declare instance variables.
	
	/**
	 * The number of credit hours each student enrolls for.
	 */
    private int mCredits;
    
    /**
     * The first name of each student.
     */
    private String mFirstName;
    
    /**
     * The ID number of each student.
     */
    private String mID;
    
    /**
     * The last name of each student.
     */
    private String mLastName;
    
    /**
     * The tuition for each student.
     */
    private double mTuition;

    /**
     * CONSTRUCTOR STUDENT
     * Creates a Student object and initializes the mId, mFirstName, and mLastName instance
     * variables.
     */
    public Student ()
    {
    	this(null, null, null);
    	// empty constructor
    }
    
    /**
     * CONSTRUCTOR STUDENT
     * Creates a Student object and initializes the mId, mFirstName, and mLastName instance
     * variables.
     * 
     * @param pID
     * @param pFirstName
     * @param pLastName
     */
    public Student (String pID, String pFirstName, String pLastName)
    {
    	setID(pID);
    	setFirstName(pFirstName);
    	setLastName(pLastName);
    }

    /**
     * ABSTRACT METHOD CALCTUITION
     * calcTuition() is to be implemented by subclasses of Student. Remember that abstract methods
     * are not implemented in a superclass but must either be implemented in a subclass, or if not,
     * then the subclass also becomes an abstract class. The reason calcTuition() is abstract
     * and intended to be implemented by the subclasses of Student is because how we calculate the
     * tuition for an OnCampusStudent is different than how we calculate the tuition for an Online-
     * Student.
     */
    abstract void calcTuition();

    /**
     * METHOD COMPARETO
     * The java.lang.Comparable<T> interface declares one method int compareTo(T obj) that must be
     * implemented by any class which implements the interface. This method is called from
     * MergeSort.merge() to compare the mTuition fields of two Students.
     *
     * Compares the mTuition fields of 'this' Student and pStudent. Returns -1 if this Student's
     * mTuition value is less than pStudent's mTuition value. Returns 0 if this Student's mTuition
     * field is equal to pStudent's mTuition field. Finally, returns 1 if this Student's mTuition
     * field is greater than pStudent's mTuition value.
     *
     * Note that the mTuition values are doubles, and if you recall, I showed you in the lecture
     * when we talked about interfaces and the Comparable interface a simple way to implement
     * compareTo() when the two values being compared are numbers. That is, you can do it this way
     * in one line of code, or you can write a traditional if-else statement to do it. The one-line
     * version will run faster, so I want you to implement it that way.
     */
    @Override
    public int compareTo(Student pStudent)
    {
    	int result;
    	if(this.mTuition < pStudent.mTuition) //this.mLastName.compareTo(pStudent.mLastName)<0 for name order
    		result = -1;
    	else if(this.mTuition > pStudent.mTuition)
    		result = 1;
    	else
    		result = 0;
    	return result;
    }

    /**
     * Accessor method for mCredits.
     */
    public int getCredits ()
    {
    	return mCredits;
    }

    /**
     * Accessor method for mFirstName.
     */
    public String getFirstName ()
    {
    	return mFirstName;
    }

    /**
     * Accessor method for mId.
     */
    public String getID ()
    {
    	return mID;
    }

    /**
     * Accessor method for mLastName.
     */
    public String getLastName ()
    {
    	return mLastName;
    }

    /**
     * Accessor method for mTuition.
     */
    public double getTuition ()
    {
    	return mTuition;
    }

    /**
     * Mutator method for mCredits.
     */
    public void setCredits (int pCredits)
    {
    	mCredits = pCredits;
    }

    /**
     * Mutator method for mFirstName.
     */
    public void setFirstName (String pFirstName)
    {
    	mFirstName = pFirstName;
    }

    /**
     * Mutator method for mId.
     */
    public void setID (String pID)
    {
    	mID = pID;
    }

    /**
     * Mutator method for mLastName.
     */
    public void setLastName (String pLastName)
    {
    	mLastName = pLastName;
    }

    /**
     * Mutator method for mTuition.
     */
    protected void setTuition (double pTuition)
    {
        mTuition = pTuition;
    }
}