-- MySQL dump 10.10
--
-- Host: localhost    Database: hotel
-- ------------------------------------------------------
-- Server version	5.0.18-nt

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
CREATE TABLE `book` (
  `Id` varchar(20) NOT NULL,
  `roomno` varchar(10) default NULL,
  `BookName` varchar(20) default NULL,
  `roomtypeid` int(11) default NULL,
  `BookTimeFrom` varchar(50) default NULL,
  `Price` varchar(20) default NULL,
  `phone` varchar(20) default NULL,
  `BookRemark` varchar(100) default NULL,
  PRIMARY KEY  (`Id`),
  KEY `RoomTypeId` (`roomtypeid`),
  CONSTRAINT `book_ibfk_1` FOREIGN KEY (`roomtypeid`) REFERENCES `roomtype` (`RoomTypeId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `book`
--


/*!40000 ALTER TABLE `book` DISABLE KEYS */;
LOCK TABLES `book` WRITE;
INSERT INTO `book` VALUES ('20212021-03-08-16:13','3','哈哈',1,'2021-03-08-16:13','100','12345678910',NULL),('20212021-03-10-17:34','8','哈哈',3,'2021-03-10-17:34','200','651651651',NULL),('20212021-03-12-15:58','6','哈哈',2,'2021-03-12-15:58','150','655353153',NULL),('20212023-04-08-00:18','12','114514',4,'2023-04-08-00:18','50','114514',NULL),('20212023-04-08-00:23','11','114514',3,'2023-04-08-00:23','200','114514',NULL),('20212023-04-08-13:16','4','123',2,'2023-04-08-13:16','150','114514',NULL),('20212023-04-08-14:03','9','1111',4,'2023-04-08-14:03','50','',NULL),('20212023-04-08-14:09','5','1230',2,'2023-04-08-14:09','150','',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `book` ENABLE KEYS */;

--
-- Table structure for table `currentuser`
--

DROP TABLE IF EXISTS `currentuser`;
CREATE TABLE `currentuser` (
  `UserName` varchar(30) NOT NULL,
  `UserType` varchar(30) NOT NULL,
  `UserPwd` varchar(30) NOT NULL,
  PRIMARY KEY  (`UserName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `currentuser`
--


/*!40000 ALTER TABLE `currentuser` DISABLE KEYS */;
LOCK TABLES `currentuser` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `currentuser` ENABLE KEYS */;

--
-- Table structure for table `customelogblog`
--

DROP TABLE IF EXISTS `customelogblog`;
CREATE TABLE `customelogblog` (
  `CustomeName` varchar(20) NOT NULL,
  `custometype` varchar(20) default NULL,
  `CustomePwd` varchar(20) NOT NULL,
  PRIMARY KEY  (`CustomeName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `customelogblog`
--


/*!40000 ALTER TABLE `customelogblog` DISABLE KEYS */;
LOCK TABLES `customelogblog` WRITE;
INSERT INTO `customelogblog` VALUES ('1230','顾客','123456');
UNLOCK TABLES;
/*!40000 ALTER TABLE `customelogblog` ENABLE KEYS */;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
CREATE TABLE `customer` (
  `Id` int(11) NOT NULL auto_increment,
  `CustomerName` varchar(100) default NULL,
  `CustomerSex` varchar(4) default NULL,
  `CustomerPassword` varchar(100) default NULL,
  `CustomerPhone` varchar(20) default NULL,
  `CustomerAddress` varchar(50) default NULL,
  `CustomerData` varchar(50) default NULL,
  `CustomerRemark` varchar(100) default NULL,
  PRIMARY KEY  (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `customer`
--


/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
LOCK TABLES `customer` WRITE;
INSERT INTO `customer` VALUES (1,'咸鱼','男','123456','114514','地球村','0',''),(2,'小王','nv','123456','114514','地球村','0',''),(3,'小明','男','123456','12345678911','山西晋中','2021-03-10 09:07:11 周六',''),(4,'小红','男','123456','516516515','榆次','2021-03-12 16:00:59 周五',''),(5,'小哼','女','123789','789456','山西晋中','2021-03-16','明天早上取'),(6,'114514','','123456','114514','地球村','2023/4/8',''),(7,'114514','','123456','114514','地球村','2023/4/8',''),(8,'123','男','123456','114514','地球村','2023-04-08 13:16:03 周六',''),(9,'1111','男','1111','1111','','2023-04-08 14:03:15 周六',''),(10,'1230','男','1230','','','2023-04-08 14:08:38 周六','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;

--
-- Table structure for table `inroom`
--

DROP TABLE IF EXISTS `inroom`;
CREATE TABLE `inroom` (
  `RoomNo` varchar(20) default NULL,
  `RoomTypeId` int(11) default NULL,
  `InRoomTime` varchar(20) default NULL,
  `InRoomName` varchar(20) default NULL,
  `InRoomIdCard` varchar(18) default NULL,
  `InRoomGender` varchar(4) default NULL,
  `InRoomPhone` varchar(20) default NULL,
  `InRoomCash` varchar(20) default NULL,
  `InRoomOrder` varchar(50) NOT NULL,
  `InRoomRemark` varchar(100) default NULL,
  PRIMARY KEY  (`InRoomOrder`),
  KEY `RoomTypeId` (`RoomTypeId`),
  KEY `RoomNo` (`RoomNo`),
  CONSTRAINT `inroom_ibfk_1` FOREIGN KEY (`RoomTypeId`) REFERENCES `roomtype` (`RoomTypeId`),
  CONSTRAINT `inroom_ibfk_2` FOREIGN KEY (`RoomNo`) REFERENCES `room` (`RoomNo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `inroom`
--


/*!40000 ALTER TABLE `inroom` DISABLE KEYS */;
LOCK TABLES `inroom` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `inroom` ENABLE KEYS */;

--
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
CREATE TABLE `log` (
  `time` varchar(50) default NULL,
  `do` varchar(11) default NULL,
  `can` varchar(11) default NULL,
  `user` varchar(11) default NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `log`
--


/*!40000 ALTER TABLE `log` DISABLE KEYS */;
LOCK TABLES `log` WRITE;
INSERT INTO `log` VALUES ('2021-02-25 21:41:08 周四','登录','登录系统','管理员'),('2021-02-25 22:10:09 周四','登录','登录系统','管理员'),('2021-02-25 22:14:15 周四','登录','登录系统','管理员'),('2021-02-25 22:16:58 周四','登录','登录系统','管理员'),('2021-02-12 00:12:14 周五','注册','新用户注册','哈哈'),('2021-02-26 00:12:29 周五','登录系统','顾客','哈哈'),('2021-02-26 00:13:23 周五','修改信息','客户','哈哈'),('2021-02-26 00:21:04 周五','登录系统','顾客','哈哈'),('2021-02-26 00:22:10 周五','修改信息','客户','哈哈'),('2021-02-26 00:25:32 周五','登录系统','顾客','哈哈'),('2021-02-26 00:25:51 周五','登录系统','顾客','哈哈'),('2021-02-26 00:26:28 周五','修改信息','客户','哈哈'),('2021-02-26 00:28:16 周五','登录系统','顾客','哈哈'),('2021-02-26 00:30:52 周五','登录','登录系统','管理员'),('2021-02-26 00:34:24 周五','备份数据库','备份全部数据','admin'),('2021-02-26 00:34:46 周五','备份数据库','备份全部数据','admin'),('2021-02-26 17:04:37 周五','登录','登录系统','管理员'),('2021-02-26 17:43:41 周五','登录','登录系统','管理员'),('2021-02-26 17:50:56 周五','登录','登录系统','管理员'),('2021-02-26 17:55:37 周五','登录','登录系统','管理员'),('2021-02-26 17:59:06 周五','登录','登录系统','管理员'),('2021-02-26 18:00:02 周五','登录','登录系统','管理员'),('2021-02-26 18:01:06 周五','登录','登录系统','管理员'),('2021-02-26 18:04:08 周五','登录','登录系统','管理员'),('2021-02-26 18:07:29 周五','登录','登录系统','管理员'),('2021-02-26 18:14:06 周五','登录','登录系统','管理员'),('2021-02-26 18:20:11 周五','登录','登录系统','管理员'),('2021-02-26 18:20:56 周五','登录','登录系统','管理员'),('2021-02-26 18:23:10 周五','登录','登录系统','管理员'),('2021-02-26 18:27:14 周五','登录','登录系统','管理员'),('2021-02-26 18:29:22 周五','登录','登录系统','管理员'),('2021-02-26 18:33:40 周五','登录','登录系统','管理员'),('2021-02-26 18:58:27 周五','登录','登录系统','管理员'),('2021-02-26 19:01:14 周五','登录','登录系统','管理员'),('2021-02-26 19:06:05 周五','登录','登录系统','管理员'),('2021-02-26 19:07:42 周五','登录','登录系统','管理员'),('2021-02-26 19:10:43 周五','登录','登录系统','管理员'),('2021-02-26 19:13:19 周五','登录','登录系统','管理员'),('2021-02-26 19:24:33 周五','登录','登录系统','管理员'),('2021-02-26 19:30:33 周五','登录','登录系统','管理员'),('2021-02-26 19:39:21 周五','登录','登录系统','管理员'),('2021-02-26 19:40:51 周五','登录','登录系统','管理员'),('2021-02-26 19:43:04 周五','登录','登录系统','管理员'),('2021-02-26 19:48:08 周五','登录','登录系统','管理员'),('2021-02-26 20:01:11 周五','登录','登录系统','管理员'),('2021-02-26 20:02:40 周五','登录','登录系统','管理员'),('2021-02-26 20:07:07 周五','登录','登录系统','管理员'),('2021-02-26 20:08:17 周五','登录','登录系统','管理员'),('2021-02-26 20:15:36 周五','登录','登录系统','管理员'),('2021-02-26 20:22:29 周五','登录','登录系统','管理员'),('2021-02-26 20:46:20 周五','登录','登录系统','管理员'),('2021-02-26 20:53:36 周五','登录','登录系统','管理员'),('2021-02-26 21:10:03 周五','登录','登录系统','管理员'),('2021-02-26 21:15:24 周五','登录','登录系统','管理员'),('2021-02-26 21:17:34 周五','登录','登录系统','管理员'),('2021-02-26 21:25:14 周五','登录','登录系统','管理员'),('2021-02-26 21:29:36 周五','登录系统','顾客','哈哈'),('2021-02-26 21:32:24 周五','登录系统','顾客','哈哈'),('2021-02-26 21:34:14 周五','登录系统','顾客','哈哈'),('2021-02-26 21:36:38 周五','登录系统','顾客','哈哈'),('2021-02-26 21:37:46 周五','登录系统','顾客','哈哈'),('2021-02-26 21:39:00 周五','登录系统','顾客','哈哈'),('2021-02-26 21:40:15 周五','登录系统','顾客','哈哈'),('2021-02-26 21:44:35 周五','登录系统','顾客','哈哈'),('2021-02-26 21:48:56 周五','登录系统','顾客','哈哈'),('2021-02-26 21:55:59 周五','登录系统','顾客','哈哈'),('2021-02-26 22:03:24 周五','登录系统','顾客','哈哈'),('2021-02-26 22:07:08 周五','登录系统','顾客','哈哈'),('2021-02-26 22:09:05 周五','登录系统','顾客','哈哈'),('2021-02-26 22:11:48 周五','登录','登录系统','管理员'),('2021-02-26 23:22:42 周五','登录系统','顾客','哈哈'),('2021-02-26 23:25:11 周五','登录','登录系统','管理员'),('2021-02-27 00:48:08 周六','登录系统','顾客','哈哈'),('2021-02-27 00:54:23 周六','登录系统','顾客','哈哈'),('2021-02-27 01:48:01 周六','登录系统','顾客','哈哈'),('2021-02-27 01:52:39 周六','登录系统','顾客','哈哈'),('2021-02-27 01:54:18 周六','登录系统','顾客','哈哈'),('2021-02-27 01:58:13 周六','登录系统','顾客','哈哈'),('2021-02-27 02:02:27 周六','登录','登录系统','管理员'),('2021-02-27 02:34:47 周六','登录','登录系统','管理员'),('2021-02-27 02:37:32 周六','登录系统','顾客','哈哈'),('2021-02-27 02:55:00 周六','登录','登录系统','管理员'),('2021-02-27 02:55:57 周六','登录系统','顾客','哈哈'),('2021-02-27 15:33:39 周六','登录系统','顾客','哈哈'),('2021-02-27 15:34:44 周六','登录','登录系统','管理员'),('2021-02-28 00:23:48 周日','登录系统','顾客','哈哈'),('2021-02-28 00:24:20 周日','登录','登录系统','管理员'),('2021-02-28 00:28:01 周日','登录','登录系统','管理员'),('2021-02-28 00:49:13 周日','登录','登录系统','管理员'),('2021-02-28 00:49:57 周日','修改房间价格','房间价格改为120','管理员'),('2021-02-28 00:54:49 周日','修改房间价格','房间价格改为120','管理员'),('2021-02-28 00:56:10 周日','登录','登录系统','管理员'),('2021-02-28 00:56:52 周日','修改洗衣机价格','洗衣机价格改为60','管理员'),('2021-02-28 00:59:07 周日','登录','登录系统','管理员'),('2021-02-28 01:02:09 周日','登录','登录系统','管理员'),('2021-02-28 01:02:41 周日','修改洗衣机价格','洗衣机价格改为60','管理员'),('2021-02-28 01:05:54 周日','登录','登录系统','管理员'),('2021-02-28 02:23:32 周日','登录系统','顾客','哈哈'),('2021-02-28 02:27:04 周日','登录','登录系统','管理员'),('2021-02-28 02:35:40 周日','登录','登录系统','管理员'),('2021-03-07 09:21:24 周日','登录系统','顾客','哈哈'),('2021-03-07 09:23:08 周日','登录','登录系统','管理员'),('2021-03-07 09:23:55 周日','修改洗衣机价格','洗衣机价格改为50','管理员'),('2021-03-07 09:24:06 周日','修改洗衣机价格','洗衣机价格改为50','管理员'),('2021-03-07 09:27:09 周日','登录','登录系统','管理员'),('2021-03-07 09:46:11 周日','登录','登录系统','管理员'),('2021-03-07 09:46:34 周日','修改洗衣机价格','洗衣机价格改为60','管理员'),('2021-03-07 10:04:43 周日','登录','登录系统','管理员'),('2021-03-07 10:06:06 周日','登录','登录系统','管理员'),('2021-03-07 10:32:21 周日','登录系统','顾客','哈哈'),('2021-03-07 16:08:44 周日','登录','登录系统','管理员'),('2021-03-07 16:08:58 周日','修改洗衣机价格','洗衣机价格改为50','管理员'),('2021-03-07 16:10:45 周日','登录系统','顾客','哈哈'),('2021-03-07 16:11:14 周日','修改信息','客户','哈哈'),('2021-03-07 16:11:28 周日','修改信息','客户','哈哈'),('2021-03-07 16:14:44 周日','登录','登录系统','管理员'),('2021-03-07 16:22:47 周日','登录系统','顾客','哈哈'),('2021-03-07 16:24:53 周日','登录系统','顾客','哈哈'),('2021-03-07 16:27:54 周日','登录系统','顾客','小王'),('2021-03-07 16:30:09 周日','登录系统','顾客','小王'),('2021-03-07 16:33:24 周日','登录系统','顾客','哈哈'),('2021-03-07 16:37:20 周日','登录系统','顾客','哈哈'),('2021-03-07 16:48:16 周日','登录系统','顾客','哈哈'),('2021-03-07 16:51:40 周日','登录系统','顾客','哈哈'),('2021-03-07 16:57:22 周日','登录系统','顾客','哈哈'),('2021-03-07 17:00:53 周日','登录系统','顾客','小王'),('2021-03-07 17:06:36 周日','登录系统','顾客','小王'),('2021-03-07 17:12:04 周日','登录系统','顾客','哈哈'),('2021-03-07 17:16:50 周日','登录系统','顾客','小王'),('2021-03-07 17:27:17 周日','登录系统','顾客','哈哈'),('2021-03-07 17:28:53 周日','登录系统','顾客','哈哈'),('2021-03-07 17:31:10 周日','登录系统','顾客','哈哈'),('2021-03-07 17:32:57 周日','登录系统','顾客','哈哈'),('2021-03-07 17:36:06 周日','登录系统','顾客','小王'),('2021-03-07 17:36:38 周日','登录','登录系统','管理员'),('2021-03-07 17:57:37 周日','登录系统','顾客','哈哈'),('2021-03-07 17:58:54 周日','登录','登录系统','管理员'),('2021-03-07 18:17:34 周日','登录','登录系统','管理员'),('2021-03-07 18:18:35 周日','来客登记','客人预定洗衣机','管理员'),('2021-03-07 18:24:07 周日','登录','登录系统','管理员'),('2021-03-07 18:35:00 周日','登录','登录系统','管理员'),('2021-03-07 18:35:46 周日','来客登记','客人预定洗衣机','管理员'),('2021-03-07 19:57:33 周日','登录系统','顾客','哈哈'),('2021-03-07 19:58:34 周日','登录','登录系统','管理员'),('2021-03-07 20:03:25 周日','登录系统','顾客','哈哈'),('2021-03-07 20:03:48 周日','登录系统','顾客','哈哈'),('2021-03-07 20:04:04 周日','登录系统','顾客','哈哈'),('2021-03-07 20:04:25 周日','登录系统','顾客','哈哈'),('2021-03-07 20:09:23 周日','登录','登录系统','管理员'),('2021-03-07 20:15:48 周日','登录系统','顾客','哈哈'),('2021-03-07 20:17:03 周日','登录','登录系统','管理员'),('2021-03-07 20:36:24 周日','登录','登录系统','管理员'),('2021-03-07 20:56:59 周日','登录','登录系统','管理员'),('2021-03-07 21:00:21 周日','登录','登录系统','管理员'),('2021-03-07 21:13:47 周日','登录','登录系统','管理员'),('2021-03-07 21:18:40 周日','登录','登录系统','管理员'),('2021-03-07 21:25:32 周日','登录','登录系统','管理员'),('2021-03-07 21:40:33 周日','登录','登录系统','管理员'),('2021-03-07 21:44:39 周日','登录','登录系统','管理员'),('2021-03-08 09:16:59 周一','登录','登录系统','管理员'),('2021-03-08 11:21:25 周一','登录','登录系统','管理员'),('2021-03-08 11:25:40 周一','登录','登录系统','管理员'),('2021-03-08 11:26:45 周一','登录系统','顾客','哈哈'),('2021-03-08 15:49:45 周一','登录系统','顾客','哈哈'),('2021-03-08 15:56:50 周一','登录系统','顾客','哈哈'),('2021-03-08 16:13:34 周一','登录系统','顾客','哈哈'),('2021-03-08 16:14:16 周一','登录','登录系统','管理员'),('2021-03-08 16:36:44 周一','登录系统','顾客','哈哈'),('2021-03-08 16:37:15 周一','登录','登录系统','管理员'),('2021-03-08 16:39:54 周一','登录','登录系统','管理员'),('2021-03-10 17:33:49 周三','登录系统','顾客','哈哈'),('2021-03-10 17:35:23 周三','登录','登录系统','管理员'),('2021-03-10 20:00:54 周三','登录','登录系统','管理员'),('2021-03-10 20:03:35 周三','登录','登录系统','管理员'),('2021-03-10 20:14:06 周三','登录','登录系统','管理员'),('2021-03-10 20:40:09 周三','登录','登录系统','管理员'),('2021-03-10 20:52:31 周三','登录','登录系统','管理员'),('2021-03-10 21:30:08 周三','登录','登录系统','管理员'),('2021-03-10 21:33:33 周三','登录','登录系统','管理员'),('2021-03-10 21:36:12 周三','登录','登录系统','管理员'),('2021-03-10 21:42:56 周三','登录','登录系统','管理员'),('2021-03-10 21:51:40 周三','注册','新用户注册','小明'),('2021-03-10 21:51:55 周三','登录系统','顾客','小明'),('2021-03-10 21:52:50 周三','修改信息','客户','小明'),('2021-03-10 21:53:03 周三','修改信息','客户','小明'),('2021-03-10 22:02:01 周三','登录系统','顾客','小明'),('2021-03-10 22:05:30 周三','登录系统','顾客','小明'),('2021-03-10 22:09:41 周三','登录系统','顾客','小明'),('2021-03-10 22:10:13 周三','修改信息','顾客','管理员'),('2021-03-10 22:11:06 周三','登录','登录系统','管理员'),('2021-03-10 22:27:08 周三','登录','登录系统','管理员'),('2021-03-10 22:30:08 周三','登录','登录系统','管理员'),('2021-03-10 22:31:45 周三','登录','登录系统','管理员'),('2021-03-11 15:07:46 周四','登录','登录系统','管理员'),('2021-03-11 15:08:33 周四','登录','登录系统','管理员'),('2021-03-11 15:25:01 周四','登录','登录系统','管理员'),('2021-03-11 15:27:01 周四','登录','登录系统','管理员'),('2021-03-11 15:28:52 周四','登录','登录系统','管理员'),('2021-03-11 15:32:11 周四','登录','登录系统','管理员'),('2021-03-11 15:34:45 周四','登录','登录系统','管理员'),('2021-03-11 16:12:24 周四','登录','登录系统','管理员'),('2021-03-11 16:47:08 周四','登录','登录系统','管理员'),('2021-03-12 15:23:40 周五','登录','登录系统','管理员'),('2021-03-12 15:49:26 周五','注册','新用户注册','小张'),('2021-03-12 15:50:17 周五','登录系统','顾客','小张'),('2021-03-12 15:57:58 周五','登录系统','顾客','哈哈'),('2021-03-12 15:58:57 周五','登录','登录系统','管理员'),('2021-03-12 16:01:05 周五','注册','新用户注册','小红'),('2021-03-14 10:51:00 周日','登录','登录系统','管理员'),('2021-03-14 10:54:15 周日','登录','登录系统','管理员'),('2021-03-14 10:55:23 周日','备份数据库','备份全部数据','管理员'),('2021-03-16 19:24:40 周二','注册','新用户注册','小哼'),('2021-03-16 19:25:25 周二','登录系统','顾客','小哼'),('2021-03-16 19:27:39 周二','修改信息','顾客','管理员'),('2021-03-16 19:28:12 周二','登录','登录系统','管理员'),('2021-04-13 15:53:12 周二','登录','登录系统','管理员'),('2021-04-13 15:53:53 周二','登录系统','顾客','哈哈'),('2021-04-13 15:54:07 周二','登录','登录系统','管理员'),('2021-04-13 16:00:16 周二','登录','登录系统','管理员'),('2021-04-13 16:15:23 周二','登录','登录系统','管理员'),('2021-04-13 17:43:14 周二','登录','登录系统','管理员'),('2021-04-13 18:08:15 周二','登录','登录系统','管理员'),('2021-04-13 18:17:46 周二','登录','登录系统','管理员'),('2021-04-13 18:22:56 周二','登录','登录系统','管理员'),('2021-04-13 18:27:43 周二','登录','登录系统','管理员'),('2021-04-13 18:28:08 周二','登录','登录系统','管理员'),('2023-04-03 21:48:39 周一','注册','新用户注册','114514'),('2023-04-03 21:48:46 周一','注册','新用户注册','114514'),('2023-04-03 21:49:07 周一','登录系统','顾客','114514'),('2023-04-05 10:24:31 周三','登录系统','顾客','114514'),('2023-04-06 17:02:30 周四','登录系统','顾客','114514'),('2023-04-06 17:08:44 周四','登录','登录系统','管理员'),('2023-04-06 17:27:15 周四','登录','登录系统','管理员'),('2023-04-06 22:16:47 周四','登录系统','顾客','114514'),('2023-04-06 22:40:48 周四','登录','登录系统','管理员'),('2023-04-07 22:09:04 周五','登录系统','组员','114514'),('2023-04-07 22:10:16 周五','登录','登录系统','监督官'),('2023-04-07 22:12:51 周五','备份数据库','备份全部数据','管理员'),('2023-04-07 22:54:10 周五','登录系统','组员','114514'),('2023-04-07 23:02:48 周五','登录系统','组员','114514'),('2023-04-07 23:18:50 周五','登录系统','组员','114514'),('2023-04-07 23:19:20 周五','登录系统','组员','114514'),('2023-04-07 23:20:24 周五','登录','登录系统','监督官'),('2023-04-07 23:23:36 周五','登录系统','组员','114514'),('2023-04-08 00:10:05 周六','登录系统','组员','114514'),('2023-04-08 00:13:30 周六','登录系统','组员','114514'),('2023-04-08 00:16:43 周六','登录系统','组员','114514'),('2023-04-08 00:18:03 周六','修改信息','组员','监督官'),('2023-04-08 00:18:23 周六','修改信息','组员','监督官'),('2023-04-08 00:21:13 周六','登录系统','组员','114514'),('2023-04-08 00:22:52 周六','登录系统','组员','114514'),('2023-04-08 00:24:37 周六','登录','登录系统','监督官'),('2023-04-08 09:16:51 周六','登录系统','组员','114514'),('2023-04-08 09:22:28 周六','登录系统','组员','114514'),('2023-04-08 09:22:45 周六','登录','登录系统','监督官'),('2023-04-08 09:24:59 周六','登录','登录系统','监督官'),('2023-04-08 09:27:21 周六','登录','登录系统','监督官'),('2023-04-08 09:31:10 周六','登录','登录系统','监督官'),('2023-04-08 09:47:50 周六','登录','登录系统','监督官'),('2023-04-08 09:49:47 周六','备份数据库','备份全部数据','管理员'),('2023-04-08 13:16:03 周六','注册','新用户注册','123'),('2023-04-08 13:16:17 周六','登录系统','组员','123'),('2023-04-08 13:17:24 周六','修改信息','组员','监督官'),('2023-04-08 13:17:39 周六','修改信息','组员','监督官'),('2023-04-08 13:18:04 周六','登录','登录系统','监督官'),('2023-04-08 13:19:59 周六','备份数据库','备份全部数据','管理员'),('2023-04-08 13:49:00 周六','登录','登录系统','监督官'),('2023-04-08 13:56:09 周六','登录系统','组员','114514'),('2023-04-08 14:03:15 周六','注册','新用户注册','1111'),('2023-04-08 14:03:28 周六','登录系统','组员','1111'),('2023-04-08 14:04:08 周六','登录','登录系统','监督官'),('2023-04-08 14:04:42 周六','备份数据库','备份全部数据','监督官'),('2023-04-08 14:08:38 周六','注册','新用户注册','1230'),('2023-04-08 14:08:46 周六','登录系统','组员','1230'),('2023-04-08 14:09:26 周六','登录','登录系统','监督官');
UNLOCK TABLES;
/*!40000 ALTER TABLE `log` ENABLE KEYS */;

--
-- Table structure for table `outbook`
--

DROP TABLE IF EXISTS `outbook`;
CREATE TABLE `outbook` (
  `Id` varchar(20) NOT NULL,
  `roomno` varchar(10) default NULL,
  `BookName` varchar(20) default NULL,
  `roomtypeid` int(11) default NULL,
  `BookTimeFrom` varchar(50) default NULL,
  `Price` varchar(20) default NULL,
  `phone` varchar(20) default NULL,
  `BookRemark` varchar(100) default NULL,
  PRIMARY KEY  (`Id`),
  KEY `RoomTypeId` (`roomtypeid`),
  CONSTRAINT `outbook_ibfk_1` FOREIGN KEY (`roomtypeid`) REFERENCES `roomtype` (`RoomTypeId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `outbook`
--


/*!40000 ALTER TABLE `outbook` DISABLE KEYS */;
LOCK TABLES `outbook` WRITE;
INSERT INTO `outbook` VALUES ('20212021-03-07-18:35','5','小哈',2,'2021-03-07-21:45','150','12345678911',NULL),('20212021-03-08-16:14','6','哈哈',2,'2021-03-08-16:17','150','12345678910',NULL),('20212021-03-08-16:36','4','哈哈',2,'2021-03-08-16:40','150','4894651651',NULL),('20212021-03-08-16:37','12','哈哈',4,'2021-03-08-16:37','50','4894651651',NULL),('20212021-03-16-19:26','12','小哼',4,'2021-03-16-19:29','50','789456',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `outbook` ENABLE KEYS */;

--
-- Table structure for table `room`
--

DROP TABLE IF EXISTS `room`;
CREATE TABLE `room` (
  `RoomNo` varchar(20) NOT NULL,
  `RoomTypeId` int(11) default NULL,
  `RoomState` varchar(50) default NULL,
  `RoomRemark` varchar(100) default NULL,
  PRIMARY KEY  (`RoomNo`),
  KEY `RoomTypeId` (`RoomTypeId`),
  CONSTRAINT `room_ibfk_1` FOREIGN KEY (`RoomTypeId`) REFERENCES `roomtype` (`RoomTypeId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `room`
--


/*!40000 ALTER TABLE `room` DISABLE KEYS */;
LOCK TABLES `room` WRITE;
INSERT INTO `room` VALUES ('1',1,'空',NULL),('10',4,'空',NULL),('11',4,'满',NULL),('12',4,'满',NULL),('2',1,'空',NULL),('3',1,'满',NULL),('4',2,'满',NULL),('5',2,'满',NULL),('6',2,'满',NULL),('7',3,'维修',NULL),('8',3,'满',NULL),('9',3,'满',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `room` ENABLE KEYS */;

--
-- Table structure for table `roomtype`
--

DROP TABLE IF EXISTS `roomtype`;
CREATE TABLE `roomtype` (
  `RoomTypeId` int(11) NOT NULL auto_increment,
  `Typename` varchar(20) default NULL,
  `TypePrice` int(11) default NULL,
  PRIMARY KEY  (`RoomTypeId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `roomtype`
--


/*!40000 ALTER TABLE `roomtype` DISABLE KEYS */;
LOCK TABLES `roomtype` WRITE;
INSERT INTO `roomtype` VALUES (1,'(1)低调豪华有内涵',6666),(2,'(2)杰哥的小屋',114514),(3,'(3)米奇妙妙屋',5555),(4,'(4)比奇堡三剑客',1111);
UNLOCK TABLES;
/*!40000 ALTER TABLE `roomtype` ENABLE KEYS */;

--
-- Table structure for table `staff`
--

DROP TABLE IF EXISTS `staff`;
CREATE TABLE `staff` (
  `StaffNo` varchar(20) NOT NULL,
  `StaffName` varchar(30) default NULL,
  `StaffPassword` varchar(100) default NULL,
  `StaffSex` varchar(4) default NULL,
  `StaffAddress` varchar(50) default NULL,
  `StaffType` varchar(20) default NULL,
  `StaffRemark` varchar(100) default NULL,
  PRIMARY KEY  (`StaffNo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `staff`
--


/*!40000 ALTER TABLE `staff` DISABLE KEYS */;
LOCK TABLES `staff` WRITE;
INSERT INTO `staff` VALUES ('1001','admin','000000','男','北京市','管理员',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `staff` ENABLE KEYS */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

