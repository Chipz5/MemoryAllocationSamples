namespace Engine
{
	namespace Timing
	{

		inline double ConvertSecondsToMilliseconds(double i_Seconds)
		{
			return i_Seconds * 1000.0;
		}

		inline double ConvertPerSecondToMillisecond(double i_PerSecond)
		{
			return i_PerSecond / 1000.0;
		}

	}
}