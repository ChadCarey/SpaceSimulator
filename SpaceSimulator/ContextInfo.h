namespace Init
{

	//OpenGL versions
	struct ContextInfo
	{
		int major_version, minor_version;
		bool core;

		ContextInfo()//default
		{
			major_version = 4;
			minor_version = 2;
			core = true;
		}

		ContextInfo(int major_version, int minor_version, bool core)
		{
			this->major_version = major_version;
			this->minor_version = minor_version;
			this->core = core;
		}

		ContextInfo(const ContextInfo& origonal)
		{
			this->major_version = origonal.major_version;
			this->minor_version = origonal.minor_version;
		}

		ContextInfo& operator=(const ContextInfo& origonal)
		{
			this->major_version = origonal.major_version;
			this->minor_version = origonal.minor_version;
			this->core = origonal.core;
		}
	};
}
