
methodmap CUtlVector < Handle
{
	public native CUtlVector(int elemsize);
	
	public native int Count();
	
	public native int AddToTail(any val);
	
	public native any Get(int i);
	
	public bool IsEmpty()
	{
		return (this.Count() == 0);
	}
}
