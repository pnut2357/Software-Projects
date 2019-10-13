/***************************************************************************************************
 * CLASS: OnCampusStudent
 *
 * DESCRIPTION
 * OnCampusStudent is a child class of the abstract class Student. Based on the information given in
 * 'student.dat', the overridden method calcTuition() calculates the tuition for each Student. 
 *
 * COURSE AND PROJECT INFO
 * CSE205 Object Oriented Programming and Data Structure, 2019 Spring
 * Project Number: project 03
 *
 * AUTHOR
 * @author Jaehyuk Choi, jchoi154, jchoi154@asu.edu
 **************************************************************************************************/
public class OnCampusStudent extends Student
{
	/**
     * The constant to check if the Student is a resident.
     */
	public final int RESIDENT = 1;
	
	/**
     * The constant to check if the Student is a non-resident.
     */
	public final int NON_RESIDENT = 2;
	
	/**
	 * Residential identity for tuition calculation. 
	 */
	private int mResident;
	
	/**
     * The data member for additional program fee.
     */
	private double mProgramFee;
	
	/**
	 * CONSTRUCTOR ONCAMPUSSTUDENT
	 * Uses the super class's constructor which creates a Student object and initializes the mId, mFirstName, and mLastName instance
     * variables.
     * 
	 * @param pID
	 * @param pFirstName
	 * @param pLastName
	 */
	public OnCampusStudent (String pID, String pFirstName, String pLastName)
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
		if(getResidency() == RESIDENT)
			t = TuitionConstants.ONCAMP_RES_BASE;
		else
			t = TuitionConstants.ONCAMP_NONRES_BASE;
		
		t += getProgramFee();
		
		if(getCredits() > TuitionConstants.ONCAMP_MAX_CREDITS)
			t += (getCredits() - TuitionConstants.ONCAMP_MAX_CREDITS)*TuitionConstants.ONCAMP_ADD_CREDITS;
		
		setTuition(t);
	}
	
	/**
	 * Accessor method for mProgramFee.
	 */
	public double getProgramFee()
	{
		return mProgramFee;
	}
	
	/**
	 * Accessor method for mResident.
	 */
	public int getResidency()
	{
		return mResident;
	}
	
	/**
	 * Mutator method for mProgramFee.
	 */
	public void setProgramFee(double pProgramFee)
	{
		mProgramFee = pProgramFee;
	}
	
	/**
	 * Mutator method for mResident.
	 */
	public void setResidency(int pResident)
	{
		mResident = pResident;
	}
}
