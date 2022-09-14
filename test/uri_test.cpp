// Copyright (c) 2022 Daniel Schütz. All rights reserved.
// MIT License

#include <gtest/gtest.h>
#include <salzaverde/uri.h>

using namespace salzaverde;

class URITest : public testing::Test {
public:
	void SetUp() override {
		uri = URI::parse(raw);
	}

protected:
	std::string raw = "http://example.com:1234/to/location?key1=value1&key2=value2#keyA=valueA";
	std::unique_ptr<URI> uri;
};

TEST_F(URITest, Parse) {
    EXPECT_EQ(uri->getScheme(), "http");
    EXPECT_EQ(uri->getHost(), "example.com");
    EXPECT_EQ(uri->getPort(), "1234");
    EXPECT_EQ(uri->getPath(), "/to/location");
    EXPECT_EQ(uri->getQuery(), "key1=value1&key2=value2");
    EXPECT_EQ(uri->getFragment(), "keyA=valueA");
};

TEST_F(URITest, SetScheme) {
	uri->setScheme("https");
	EXPECT_EQ(uri->getScheme(), "https");
};

TEST_F(URITest, SetSchemeWithSuffix) {
	uri->setScheme("https://");
	EXPECT_EQ(uri->getScheme(), "https");
};

TEST_F(URITest, SetHost) {
	uri->setHost("example2.com");
	EXPECT_EQ(uri->getHost(), "example2.com");
};

TEST_F(URITest, SetPort) {
	uri->setPort("5678");
	EXPECT_EQ(uri->getPort(), "5678");
};

TEST_F(URITest, SetPath) {
	uri->setPath("to/other");
	EXPECT_EQ(uri->getPath(), "/to/other");
};

TEST_F(URITest, SetPathWithPrefix) {
	uri->setPath("/to/other");
	EXPECT_EQ(uri->getPath(), "/to/other");
};

TEST_F(URITest, SetQuery) {
	uri->setQuery("key3=value3");
	EXPECT_EQ(uri->getQuery(), "key3=value3");
};

TEST_F(URITest, SetFragment) {
    uri->setFragment("keyB=valueB");
    EXPECT_EQ(uri->getFragment(), "keyB=valueB");
};

TEST_F(URITest, ToString) {
    EXPECT_EQ(uri->dump(), raw);
};

TEST_F(URITest, Scheme) {
    auto uri = URI::parse("http://");
    EXPECT_EQ(uri->getScheme(), "http");
};

TEST_F(URITest, Path) {
    auto uri = URI::parse("/some/path");
    EXPECT_EQ(uri->getPath(), "/some/path");
};

TEST_F(URITest, QueryString) {
    auto uri = URI::parse("?key1=value1");
    EXPECT_EQ(uri->getQuery(), "key1=value1");
};

TEST_F(URITest, Fragment) {
    auto uri = URI::parse("#keyC=valueC");
    EXPECT_EQ(uri->getFragment(), "keyC=valueC");
};
