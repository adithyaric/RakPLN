<?php 
header("Content-Type: application/json; charset=UTF-8");
include "koneksi.php";

// if(isset($_GET['id'])){
// 	$api = $_GET['api'];
// 	$data_id = $_GET['id'];
// 	$jml_barang = $_GET['jml'];

// 	//if($api == "2404222253KRJGRBMGL") {
// 		$data = $koneksi->query("SELECT * FROM tb_statistik WHERE id='$data_id'");
// 		$jmldata = $data->num_rows;
// 		$pecahan = $data->fetch_assoc();

// 		echo json_encode($pecahan);
// 	//}
// }

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	$data = file_get_contents("php://input");
	$json = json_decode($data, TRUE);

	$api = $json['api'];
	$perintah = $json['perintah'];

	if($api == "2404222253KRJGRBMGL") {
		$datadata = explode(",", $perintah);
		$aksi = $datadata[0];
		$id = $datadata[1];
		$jml = $datadata[2];

		$ambilData = $koneksi->query("SELECT * FROM tb_statistik WHERE id='$id'");
		$pecah = $ambilData->fetch_assoc();
		$jmlAmbil = $pecah['jumlah_barang'];


		if($aksi == "get") {
			$hasil = $jmlAmbil-(int)$jml;
			$koneksi->query("UPDATE tb_statistik SET status_update='Checkout', jumlah_barang='$hasil' WHERE id='$id'");
		}else if($aksi == "add") {
			$hasil = $jmlAmbil+(int)$jml;
			$koneksi->query("UPDATE tb_statistik SET status_update='Update', jumlah_barang='$hasil' WHERE id='$id'");
		}

		$query = $koneksi->query("SELECT * FROM tb_statistik WHERE id='$id'");
		$pecahan = $query->fetch_assoc();

		echo json_encode($pecahan);
	}
}

?>

