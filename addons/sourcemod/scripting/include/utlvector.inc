
methodmap CUtlVector < Handle
{
	public native CUtlVector();
	
	public native int Count();
	
	public native int AddToTail(any val);
	
	public native any Get(int i);
	
	public bool IsEmpty()
	{
		return (this.Count() == 0);
	}
	
	public Address GetAddress()
	{
		any address64[2];
		this.GetAddress64(address64);
		
		return address64[0];
	}
	
	public native void GetAddress64(any address[2]);
	
	public static CUtlVector FromAddress(Address address, int size = 4)
	{
		any address64[2];
		address64[0] = address;
		address64[1] = 0;
		return CUtlVector.FromAddress64(address64);
	}
	
	public static native CUtlVector FromAddress64(any address[2], int size = 4);
}
