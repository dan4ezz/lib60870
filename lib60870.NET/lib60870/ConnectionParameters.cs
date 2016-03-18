using System;

namespace lib60870
{
	public class ConnectionParameters
	{

		private int k = 12; /* number of unconfirmed APDUs in I format
		                (range: 1 .. 32767 (2^15 - 1) - sender will
		                stop transmission after k unconfirmed I messages */

		private int w = 8; /* number of unconfirmed APDUs in I format 
						      (range: 1 .. 32767 (2^15 - 1) - receiver
						      will confirm latest after w messages */

		private int t0 = 10; /* connection establishment (in s) */

		private int t1 = 15; /* timeout for transmitted APDUs in I/U format (in s)
		                   when timeout elapsed without confirmation the connection
		                   will be closed */

		private int t2 = 10; /* timeout to confirm messages (in s) */

		private int t3 = 20; /* time for test telegrams in case of idle connection */

		private int sizeOfTypeId = 1;

		private int sizeOfVSQ = 1; /* VSQ = variable sturcture qualifier */

		private int sizeOfCOT = 2; /* (parameter b) COT = cause of transmission (1/2) */

		private int originatorAddress = 0;

		private int sizeOfCA = 2; /* (parameter a) CA = common address of ASDUs (1/2) */
	
		private int sizeOfIOA = 3; /* (parameter c) IOA = information object address (1/2/3) */

		private int tcpPort = 2404;

		public ConnectionParameters ()
		{
		}

		public ConnectionParameters clone() {
			ConnectionParameters copy = new ConnectionParameters();

			copy.k = k;
			copy.w = w;
			copy.t0 = t0;
			copy.t1 = t1;
			copy.t2 = t2;
			copy.t3 = t3;
			copy.sizeOfTypeId = sizeOfTypeId;
			copy.sizeOfVSQ = sizeOfVSQ;
			copy.sizeOfCOT = sizeOfCOT;
			copy.originatorAddress = originatorAddress;
			copy.sizeOfCA = sizeOfCA;
			copy.sizeOfIOA = sizeOfIOA;
			copy.tcpPort = tcpPort;

			return copy;
		}

		public int K {
			get {
				return this.k;
			}
			set {
				k = value;
			}
		}

		public int W {
			get {
				return this.w;
			}
			set {
				w = value;
			}
		}

		public int T0 {
			get {
				return this.t0;
			}
			set {
				t0 = value;
			}
		}

		public int T1 {
			get {
				return this.t1;
			}
			set {
				t1 = value;
			}
		}

		public int T2 {
			get {
				return this.t2;
			}
			set {
				t2 = value;
			}
		}

		public int T3 {
			get {
				return this.t3;
			}
			set {
				t3 = value;
			}
		}

		public int SizeOfCOT {
			get {
				return this.sizeOfCOT;
			}
			set {
				sizeOfCOT = value;
			}
		}

		public int OriginatorAddress {
			get {
				return this.originatorAddress;
			}
			set {
				originatorAddress = value;
			}
		}

		public int SizeOfCA {
			get {
				return this.sizeOfCA;
			}
			set {
				sizeOfCA = value;
			}
		}

		public int SizeOfIOA {
			get {
				return this.sizeOfIOA;
			}
			set {
				sizeOfIOA = value;
			}
		}	


		public int SizeOfTypeId {
			get {
				return this.sizeOfTypeId;
			}
		}

		public int SizeOfVSQ {
			get {
				return this.sizeOfVSQ;
			}
		}

		public int TcpPort {
			get {
				return this.tcpPort;
			}
			set {
				tcpPort = value;
			}
		}
	}
}
