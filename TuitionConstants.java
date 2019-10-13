/***************************************************************************************************
 * CLASS: TuitionConstants (TuitionConstants.java)
 *
 * DESCRIPTION
 * TuitionConstants is a constant class for calculating a tuition for the OnCampusStudent and 
 * OnlineStudent classes. Depending on student information, the constants are used to set
 * additional fee to a tuition. 
 *
 * COURSE AND PROJECT INFO
 * CSE205 Object Oriented Programming and Data Structure, 2019 Spring
 * Project Number: project 03
 *
 * AUTHOR
 * @author Jaehyuk Choi, jchoi154, jchoi154@asu.edu
 **************************************************************************************************/

public final class TuitionConstants{
	/**
	 * The additional fee of $475 for each credit hours over 18 credits. 
	 */
	public static final int ONCAMP_ADD_CREDITS = 475;
	
	/**
	 * The maximum credit hours of 18 for the base rate of a tuition.
	 */
	public static final int ONCAMP_MAX_CREDITS = 18;
	
	/**
	 * The base rate of a tuition $14,875 for non-residents.
	 */
	public static final int ONCAMP_NONRES_BASE = 14875;
	
	/**
	 * The base rate of a tuition $7,575 for non-residents.
	 */
	public static final int ONCAMP_RES_BASE = 7575;
	
	/**
	 * The online credit hours rate $950 per credit hour for online students.
	 */
	public static final int ONLINE_CREDIT_RATE = 950;
	
	/**
	 * The additional online technology fee $75.
	 */
	public static final int ONLINE_TECH_FEE = 75;
	
}