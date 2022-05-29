<?php include "koneksi.php"; ?>
<?php include "header.php"; ?>

<h1 class="text-center">Ambil Material</h1>
<hr>

<br>

<form enctype="multipart/form-data" method="POST" class="needs-validation" novalidate>
	<div class="container">
	    <table class="table table-bordered table-hover">
			<tbody>
				<tr>
					<td width="150px">Nama Material</td>
					<td>
						<select name="nama_barang" class="form-control">
							<?php
							$getBarang = $koneksi->query("SELECT * FROM tb_statistik");
							while($ambil = $getBarang->fetch_assoc()) {
							?>
							<option value="<?php echo $ambil['nama_barang']; ?>"><?php echo $ambil['nama_barang']; ?></option>
							<?php } ?>
						</select>
					</td>
				</tr>

				<tr>
					<td>Jumlah Material</td>
					<td><input type="number" class="form-control" name="jumlah_barang" placeholder="Masukkan Jumlah Material" required></td>
				</tr>
			</tbody>
		</table>
	</div>

	<br>

	<p style="text-align: center;">
		<button class="btn btn-primary mr-2" name="update_barang">Ubah</button>
		<a type="button" class="btn btn-danger mr-2" href="index.php">Batal</a></p>

</form>

<style type="text/css">
.table {
    margin: 0 auto;
    width: auto;
}
</style>

<?php 

if(isset($_POST['update_barang'])) {
	$nama_barang = $_POST['nama_barang'];
	$jumlah_barang = $_POST['jumlah_barang'];
	// $kode_rak = $rak_kolom.$rak_baris;


	if(!empty($nama_barang) || !empty($jumlah_barang)) {
		$data = $koneksi->query("SELECT * FROM tb_statistik WHERE nama_barang='$nama_barang'");
		$jmldata = $data->num_rows;
		$pecahan = $data->fetch_assoc();
		$jml = $pecahan['jumlah_barang'];
		$hasil = $jml-(int)$jumlah_barang;
		$koneksi->query("UPDATE tb_statistik SET status_update = 'Checkout', nama_barang = '$nama_barang',  jumlah_barang = '$hasil' WHERE nama_barang = '$nama_barang'");
		
		echo "<script>alert('Material telah diambil !');</script>";
	    echo "<script>location='index.php';</script>";
	}else{
		echo "<script>alert('Mohon lengkapi semua data !');</script>";
	}
}

?>


<?php include "footer.php"; ?>