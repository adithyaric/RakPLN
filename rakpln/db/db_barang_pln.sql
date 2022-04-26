-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Apr 25, 2022 at 08:48 AM
-- Server version: 5.7.33
-- PHP Version: 7.4.19

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_barang_pln`
--

-- --------------------------------------------------------

--
-- Table structure for table `tb_statistik`
--

CREATE TABLE `tb_statistik` (
  `id` int(11) NOT NULL,
  `tgl_update` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `status_update` varchar(255) NOT NULL,
  `nama_barang` varchar(255) NOT NULL,
  `satuan_barang` varchar(255) NOT NULL,
  `jumlah_barang` int(11) NOT NULL,
  `kode_rak` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tb_statistik`
--

INSERT INTO `tb_statistik` (`id`, `tgl_update`, `status_update`, `nama_barang`, `satuan_barang`, `jumlah_barang`, `kode_rak`) VALUES
(1, '2022-04-24 15:30:32', 'Checkout', 'MCB', 'Unit', 102, '320'),
(4, '2022-04-24 16:19:59', 'Perbarui Data', 'KWH', 'PCS', 172, 'A40'),
(5, '2022-04-25 14:46:43', 'Update', 'Saklar', 'PCS', 290, 'A5');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `tb_statistik`
--
ALTER TABLE `tb_statistik`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `tb_statistik`
--
ALTER TABLE `tb_statistik`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
