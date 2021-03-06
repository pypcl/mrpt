/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          https://www.mrpt.org/                         |
   |                                                                        |
   | Copyright (c) 2005-2019, Individual contributors, see AUTHORS file     |
   | See: https://www.mrpt.org/Authors - All rights reserved.               |
   | Released under BSD License. See: https://www.mrpt.org/License          |
   +------------------------------------------------------------------------+ */

#include <mrpt/random/RandomGenerators.h>
#include <gtest/gtest.h>

TEST(Random, Randomize)
{
	using namespace mrpt::random;

	CRandomGenerator rnd;
	rnd.randomize(1);
	auto r1a = rnd.drawUniform32bit();
	rnd.randomize(2);
	auto r2a = rnd.drawUniform32bit();

	EXPECT_NE(r1a, r2a);

	rnd.randomize(1);
	auto r1abis = rnd.drawUniform32bit();
	EXPECT_EQ(r1a, r1abis);
}

TEST(Random, KnownSequence)
{
	const uint32_t seeds[5] = {1883688432U, 3775318916U, 2839366872U,
							   4182714712U, 3235295241U};

	const uint32_t psr_seq[5][30] = {
		{4116471315U, 2398331081U, 1977083486U, 2989495450U, 1967218147U,
		 3627491547U, 2191680533U, 3577186743U, 2695842082U, 323868342U,
		 1281839123U, 574469316U,  1300719084U, 715945997U,  2880042017U,
		 2046339299U, 1233788655U, 3263150238U, 1574995596U, 56602531U,
		 2871611984U, 2393996125U, 128168937U,  2998246531U, 1075745388U,
		 1855738821U, 1367740061U, 3259222690U, 2987305086U, 2079426074U},
		{4018068287U, 3387863329U, 2514983379U, 2823808154U, 3887143489U,
		 837809068U,  54838799U,   1148682864U, 3093755027U, 4242099785U,
		 2415900128U, 2696414825U, 997749501U,  3462488255U, 2360492622U,
		 1608276878U, 924703885U,  856222103U,  1357783161U, 2923118814U,
		 4031679579U, 1855867619U, 3821201070U, 232861985U,  3772460059U,
		 1991587263U, 643571312U,  1361533248U, 4204342437U, 349266075U},
		{1679280030U, 2236915811U, 3968608568U, 154617530U,  2573673130U,
		 138625755U,  3271821260U, 2944560244U, 1330652294U, 2871083222U,
		 34086655U,   3019338967U, 1446309699U, 4145900586U, 1685607532U,
		 3099431589U, 2028404010U, 264886050U,  2086069517U, 338432153U,
		 3431240677U, 121877725U,  2169116191U, 2230386811U, 3853391744U,
		 1256863550U, 2658562580U, 3427412747U, 1099822715U, 707301986U},
		{2767895938U, 722798569U,  2515742595U, 4070814356U, 1084030302U,
		 1608202756U, 2527776333U, 2397186090U, 2432391292U, 256077469U,
		 1662140178U, 2977391319U, 3363905520U, 4110605468U, 11633303U,
		 1324515573U, 4118197403U, 3432066315U, 92187713U,   2368454623U,
		 195775173U,  2347094721U, 86038886U,   1947962139U, 2660751971U,
		 2053283147U, 163927191U,  3029593818U, 3009798039U, 672542045U},
		{3199440481U, 1820165898U, 3438868004U, 1179081229U, 4025362166U,
		 494006199U,  3196336992U, 1090840637U, 1635926028U, 1628755357U,
		 2990259311U, 2494524675U, 1326880352U, 506479842U,  1396624679U,
		 810333226U,  2357879734U, 1945663543U, 3174013122U, 2808539327U,
		 2318331030U, 1211238431U, 3706490907U, 3924314845U, 1547223414U,
		 3165092293U, 3646761289U, 1781842636U, 1019702570U, 3814920358U}};

	for (int seed = 0; seed < 5; seed++)
	{
		auto& rnd = mrpt::random::getRandomGenerator();
		mrpt::random::Randomize(seeds[seed]);
		for (int i = 0; i < 30; i++)
		{
			const auto v = rnd.drawUniform32bit();
			EXPECT_EQ(v, psr_seq[seed][i]);
		}
	}
}
