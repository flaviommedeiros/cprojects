static struct fmt_tests oo_tests[] = {
	{"$oldoffice$1*de17a7f3c3ff03a39937ba9666d6e952*2374d5b6ce7449f57c9f252f9f9b53d2*e60e1185f7aecedba262f869c0236f81", "test"},
	{"$oldoffice$0*e40b4fdade5be6be329c4238e2099b8a*259590322b55f7a3c38cb96b5864e72d*2e6516bfaf981770fe6819a34998295d", "123456789012345"},
	{"$oldoffice$4*163ae8c43577b94902f58d0106b29205*87deff24175c2414cb1b2abdd30855a3*4182446a527fe4648dffa792d55ae7a15edfc4fb", "Google123"},
	/* Meet-in-the-middle candidate produced with oclHashcat -m9710 */
	/* Real pw is "hashcat", one collision is "zvDtu!" */
	{"", "zvDtu!", {"", "$oldoffice$1*d6aabb63363188b9b73a88efb9c9152e*afbbb9254764273f8f4fad9a5d82981f*6f09fd2eafc4ade522b5f2bee0eaf66d","f2ab1219ae"} },
#if PLAINTEXT_LENGTH >= 24
	/* 2003-RC4-40bit-MS-Base-Crypto-1.0_myhovercraftisfullofeels_.doc */
	{"$oldoffice$3*9f32522fe9bcb69b12f39d3c24b39b2f*fac8b91a8a578468ae7001df4947558f*f2e267a5bea45736b52d6d1051eca1b935eabf3a", "myhovercraftisfullofeels"},
	/* Test-RC4-40bit-MS-Base-DSS_myhovercraftisfullofeels_.doc */
	{"$oldoffice$3*095b777a73a10fb6bcd3e48d50f8f8c5*36902daab0d0f38f587a84b24bd40dce*25db453f79e8cbe4da1844822b88f6ce18a5edd2", "myhovercraftisfullofeels"},
	/* 2003-RC4-40bit-MS-Base-DH-SChan_myhovercraftisfullofeels_.doc */
	{"$oldoffice$3*284bc91cb64bc847a7a44bc7bf34fb69*1f8c589c6fcbd43c42b2bc6fff4fd12b*2bc7d8e866c9ea40526d3c0a59e2d37d8ded3550", "myhovercraftisfullofeels"},
	/* Test-RC4-128bit-MS-Strong-Crypto_myhovercraftisfullofeels_.doc */
	{"$oldoffice$4*a58b39c30a06832ee664c1db48d17304*986a45cc9e17e062f05ceec37ec0db17*fe0c130ef374088f3fec1979aed4d67459a6eb9a", "myhovercraftisfullofeels"},
	/* 2003-RC4-40bit-MS-Base-1.0_myhovercraftisfullofeels_.xls */
	{"$oldoffice$3*f426041b2eba9745d30c7949801f7d3a*888b34927e5f31e2703cc4ce86a6fd78*ff66200812fd06c1ba43ec2be9f3390addb20096", "myhovercraftisfullofeels"},
#endif
	/* the following hash was extracted from Proc2356.ppt (manually + by oldoffice2john.py */
	{"$oldoffice$3*DB575DDA2E450AB3DFDF77A2E9B3D4C7*AB183C4C8B5E5DD7B9F3AF8AE5FFF31A*B63594447FAE7D4945D2DAFD113FD8C9F6191BF5", "crypto"},
	{"$oldoffice$3*3fbf56a18b026e25815cbea85a16036c*216562ea03b4165b54cfaabe89d36596*91308b40297b7ce31af2e8c57c6407994b205590", "openwall"},
	{NULL}
};
