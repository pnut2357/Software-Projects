/***************************************************************************************************
 * CLASS: OnlineStudent (OnlineStudent.java)
 *
 * DESCRIPTION
 * OnlineStudent is a child class of abstract class Student. Based on the information given in
 * 'student.dat', the overridden method calcTuition() calculates the tuition for each Student. 
 *
 * COURSE AND PROJECT INFO
 * CSE205 Object Oriented Programming and Data Structure, 2019 Spring
 * Project Number: project 03
 *
 * AUTHOR
 * @author Jaehyuk Choi, jchoi154, jchoi154@asu.edu
 **************************************************************************************************/
public class OnlineStudent extends Student
{
	/**
	 * The boolean data member for additional Technology fee.
	 */
	private boolean mTechFee;
	
	/**
	 * CONSTRUCTOR ONLINESTUDENT
	 * Uses the super class's constructor which creates a Student object and initializes the mId, mFirstName, and mLastName instance
     * variables.
	 * 
	 * @param pID
	 * @param pFirstName
	 * @param pLastName
	 */
	public OnlineStudent(String pID, String pFirstName, String pLastName)
	{
		super(pID, pFirstName, pLastName);	
	}
	
	/**
	 * METHOD CALCTUITION
	 * Checks residential identity and number of credits that each Student enrolls to calculate tuition
	 */
	@Override
	public void calcTuition()
	{
		double t;
		t = getCredits()*TuitionConstants.ONLINE_CREDIT_RATE;
		if (getTechFee() == true)
			t += TuitionConstants.ONLINE_TECH_FEE;
		
		setTuition(t);
	}
	
	/**
	 * Accessor method for mTechFee.
	 */
	public boolean getTechFee()
	{
		return mTechFee;
	}
	
	/**
	 * Mutator method for mTechFee.
	 */
	public void setTechFee(boolean pTechFee)
	{
		mTechFee = pTechFee;
	}
}
