/* EEG_def.h
 *
 * Copyright (C) 2011 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#define ooSTRUCT EEG
oo_DEFINE_CLASS (EEG, Function)

	oo_LONG (d_numberOfChannels)
	oo_STRING_VECTOR (d_channelNames, d_numberOfChannels)
	oo_OBJECT (Sound, 2, d_sound)
	oo_OBJECT (TextGrid, 0, d_textgrid)

	#if oo_DECLARING
		// functions:
		public:
			void f_init (double tmin, double tmax);
			long f_getChannelNumber (const wchar *channelName);
			void f_setChannelName (long channelNumber, const wchar *a_name);
			long f_getNumberOfCapElectrodes () { return (d_numberOfChannels - 1) & ~ 15L; }   // BUG
			long f_getNumberOfExternalElectrodes () { return d_numberOfChannels - f_getNumberOfCapElectrodes () - f_getNumberOfExtraSensors (); }
			long f_getNumberOfExtraSensors () { return d_numberOfChannels & 1 ? 1 : 8; }   // BUG
			void f_setExternalElectrodeNames (const wchar *nameExg1, const wchar *nameExg2, const wchar *nameExg3, const wchar *nameExg4,
				const wchar *nameExg5, const wchar *nameExg6, const wchar *nameExg7, const wchar *nameExg8);
			void f_detrend ();
			void f_filter (double lowFrequency, double lowWidth, double highFrequency, double highWidth, bool doNotch50Hz);
			void f_subtractReference (const wchar *channelNumber1, const wchar *channelNumber2);
			void f_subtractMeanChannel (long fromChannel, long toChannel);
			void f_setChannelToZero (long channelNumber);
			void f_setChannelToZero (const wchar *channelName);
			EEG f_extractChannel (long channelNumber);
			EEG f_extractChannel (const wchar *channelName);
			Sound f_extractSound () { return Data_copy (d_sound); }
			TextGrid f_extractTextGrid () { return Data_copy (d_textgrid); }
			EEG f_extractPart (double tmin, double tmax, bool preserveTimes);
		// overridden methods:
		protected:
			virtual void v_info ();
			virtual int v_domainQuantity () { return MelderQuantity_TIME_SECONDS; }
			virtual void v_shiftX (double xfrom, double xto);
			virtual void v_scaleX (double xminfrom, double xmaxfrom, double xminto, double xmaxto);
	#endif

oo_END_CLASS (EEG)
#undef ooSTRUCT

/* End of file EEG_def.h */