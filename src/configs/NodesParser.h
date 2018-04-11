#pragma once
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include <string>
#include <vector>
#include <tox/tox.h>
#include <sodium.h>

typedef struct DHT_node
{
    std::string ip;
    std::string ipv6;
    uint16_t port;
    std::string key_hex;
    std::string key_bin;
} DHT_node;

static std::vector<DHT_node> get_dht_nodes()
{
    QString data;
    QFile file;
    file.setFileName(":/configs/nodes.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    data = file.readAll();
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject json_obj = json.object();

    std::vector<DHT_node> result;

    if (json_obj.contains("nodes") && json_obj["nodes"].isArray())
        {
            auto nodes = json_obj["nodes"].toArray();
            for (int i = 0; i < nodes.size(); ++i)
                {
                    if(nodes[i].isObject())
                        {
                            auto node = nodes[i].toObject();

                            if (!(node.contains("ipv4") && node["ipv4"].isString()) ||
                                !(node.contains("ipv6") && node["ipv6"].isString()) ||
                                !(node.contains("port") && node["port"].isDouble()) ||
                                !(node.contains("public_key") && node["public_key"].isString()))
                                {
                                    continue;
                                }
                            auto ip = node["ipv4"].toString();
                            auto ipv6 = node["ipv6"].toString();
                            auto port = static_cast<uint16_t>(node["port"].toInt());
                            auto public_key = node["public_key"].toString().toStdString();

                            unsigned char key_bin[TOX_PUBLIC_KEY_SIZE + 1] = {0};
                            sodium_hex2bin(key_bin, sizeof(key_bin),
                                           public_key.c_str(), TOX_PUBLIC_KEY_SIZE * 2, NULL, NULL, NULL);

                            result.emplace_back(DHT_node{ip.toStdString(), ipv6.toStdString(), port,
                                                         public_key, std::string((char*)&key_bin)});
                        }
                }
        }
    return result;
}

