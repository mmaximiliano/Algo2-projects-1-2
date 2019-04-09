#include <gtest/gtest.h>
#include "../src/string_map.h"


TEST(test_string_map, vacio) {
    string_map<int> vacio;
    EXPECT_TRUE(vacio.empty());
    EXPECT_EQ(vacio.count("hola"), 0);
}



TEST(test_string_map, asignar) {
    string_map<int> singleton;
    EXPECT_TRUE(singleton.empty());
    singleton["hola"] = 1;

    EXPECT_FALSE(singleton.empty());
    EXPECT_EQ(singleton["hola"], 1);
    EXPECT_EQ(singleton.size(), 1);
}



TEST(test_string_map, cincoclaves) {
    string_map<int> dicc;
    EXPECT_TRUE(dicc.empty());
    dicc["hola"] = 1;
    dicc["casa"] = 3;
    dicc["holanda"] = 4;
    dicc["camaleon"] = 17;
    dicc["curioso"] = 13;

    EXPECT_FALSE(dicc.empty());
    vector<string> clavesDel;
    clavesDel.push_back("hola");
    clavesDel.push_back("casa");
    clavesDel.push_back("holanda");
    clavesDel.push_back("camaleon");
    clavesDel.push_back("curioso");
    list<string> clavesPosta = dicc.claves();
    EXPECT_EQ(dicc.size(), 5);

    list<string>::iterator it = clavesPosta.begin();
    for (int i = 0; i < clavesDel.size(); i++) {
        EXPECT_EQ(*it, clavesDel[i]);
        it++;
    }
}



TEST(test_string_map, igualar_dos) {
    string_map<int> dicc1;
    EXPECT_TRUE(dicc1.empty());
    dicc1["camaron"] = 1;
    dicc1["colibri"] = 34;
    dicc1["ciervo"] = 7;

    string_map<int> dicc2 = dicc1;
    EXPECT_FALSE(dicc1.empty());
    EXPECT_FALSE(dicc2.empty());
    EXPECT_EQ(dicc1.size(), dicc2.size());
    EXPECT_EQ(dicc1.claves(), dicc2.claves());
}



TEST(test_string_map, at_and_count1) {
    string_map<string> dicc;
    EXPECT_TRUE(dicc.empty());
    dicc["arg"] = "Argentina";
    dicc["swe"] = "Suecia";
    dicc["den"] = "Dinamarca";
    EXPECT_FALSE(dicc.empty());
    EXPECT_EQ(dicc.size(), 3);
    EXPECT_EQ(dicc.count("arg"), 1);
    EXPECT_EQ(dicc.count("ger"), 0);
    EXPECT_EQ(dicc.count("swe"), 1);
    EXPECT_EQ(dicc.count("nor"), 0);
    EXPECT_EQ(dicc.count("den"), 1);
    EXPECT_EQ("Argentina", dicc.at("arg"));
    EXPECT_EQ("Suecia", dicc.at("swe"));
    EXPECT_EQ("Dinamarca", dicc.at("den"));
}



TEST(test_string_map, at_and_count2) {
    string_map<int> diccPerros;
    EXPECT_TRUE(diccPerros.empty());
    diccPerros["Beagle"] = 9800;
    diccPerros["Pug"] = 16000;
    diccPerros["Galgo"] = 0;
    diccPerros["Boyero de Berna"] = 20000;
    diccPerros["Golden Retriever"] = 8000;
    diccPerros["Husky Siberiano"] = 3000;
    EXPECT_FALSE(diccPerros.empty());
    EXPECT_EQ(diccPerros.size(), 6);
    EXPECT_EQ(diccPerros.count("Beagle"), 1);
    EXPECT_EQ(diccPerros.count("Rottweiler"), 0);
    EXPECT_EQ(diccPerros.count("Chihuahua"), 0);
    EXPECT_EQ(diccPerros.count("Pug"), 1);
    EXPECT_EQ(diccPerros.count("Husky Siberiano"), 1);
    EXPECT_EQ(diccPerros.count("Labrador"), 0);
    EXPECT_EQ(diccPerros.count("Cocker"), 0);
    EXPECT_EQ(diccPerros.count("Golden Retriever"), 1);
    EXPECT_EQ(9800, diccPerros.at("Beagle"));
    EXPECT_EQ(16000, diccPerros.at("Pug"));
    EXPECT_EQ(0, diccPerros.at("Galgo"));
    EXPECT_EQ(20000, diccPerros.at("Boyero de Berna"));
    EXPECT_EQ(8000, diccPerros.at("Golden Retriever"));
    EXPECT_EQ(3000, diccPerros.at("Husky Siberiano"));

}
